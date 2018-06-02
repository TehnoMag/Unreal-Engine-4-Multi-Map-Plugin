// Copyright Mickail `TehnoMag` Lukianov © 2018

#include "LevelRelations.h"
#include "Engine/Engine.h"
#include "Package.h"
#include "ShaderCompiler.h"
#include "AI/Navigation/NavigationSystem.h"
#include "IXRTrackingSystem.h"

bool ULevelRelations::LoadSubLevel(ULevelRelations* LevelRelations, const FString& LevelName)
{
	check(LevelRelations);
	const FWorldContext* RootContext = &GEngine->GetWorldContexts()[1];
	FString CurrentLevelName = RootContext->World()->GetName();
	int32 RelationID = LevelRelations->FindRelation(CurrentLevelName);

	// Issue #3
	if (RelationID < 0)
	{
		UE_LOG(LogMultiMapPlugin, Fatal, TEXT("OOps on RelationID"));
		return false;
	}

	int32 ContainerID = LevelRelations->FindContainer(RelationID, LevelName);

	if (ContainerID < 0)
	{
		UE_LOG(LogMultiMapPlugin, Fatal, TEXT("OOps on ContainerID"));
		return false;
	}

	//check if level already loaded
	FLevelContainer* Container = &LevelRelations->LevelTree[RelationID].ChildLevels[ContainerID];
	
	if (!Container->bIsLoaded)
	{
		FWorldContext* WorldContext = &GEngine->CreateNewWorldContext(EWorldType::Game);
		WorldContext->OwningGameInstance = RootContext->OwningGameInstance;

		UWorld* NewWorld = LevelRelations->LoadLevel(WorldContext, LevelName);

		LevelRelations->LevelTree[RelationID].ChildLevels[ContainerID].WorldContext = WorldContext;
		LevelRelations->LevelTree[RelationID].ChildLevels[ContainerID].bIsLoaded = true;

		return true;
	}

	return false;
}

bool ULevelRelations::LoadAllSubLevels(ULevelRelations* LevelRelations)
{
	return false;
}

int32 ULevelRelations::FindRelation(const FString& LevelName)
{
	int32 id = -1;
	for (int32 i = 0; i < LevelTree.Num(); i++)
	{
		if (LevelTree[i].RootLevel.LevelName == LevelName)
		{
			id = i;
			break;
		}
	}

	return id;
}

int32 ULevelRelations::FindContainer(const int32& RelId, const FString& LevelName)
{
	int32 id = -1;
	for (int32 i = 0; i < LevelTree[RelId].ChildLevels.Num(); i++)
	{
		if (LevelTree[RelId].ChildLevels[i].LevelName == LevelName)
		{
			id = i;
			break;
		}
	}

	return id;
}

UWorld* ULevelRelations::LoadLevel(FWorldContext* Context, const FString& Name)
{
	FURL URL(*Name);
	const FName URLMapFName = FName(*URL.Map);

	Context->OwningGameInstance->PreloadContentForURL(URL);
	UPackage* WorldPackage = NULL;
	UWorld*	NewWorld = NULL;

	UWorld::WorldTypePreLoadMap.FindOrAdd(URLMapFName);
	
	WorldPackage = FindPackage(nullptr, *URL.Map);

	if (WorldPackage == nullptr)
		//PIE drop issue if WorldType PIE 
		WorldPackage = LoadPackage(nullptr, *URL.Map, Context->WorldType == EWorldType::PIE ? LOAD_PackageForPIE : LOAD_None);

	UWorld::WorldTypePreLoadMap.Remove(URLMapFName);

	if (WorldPackage == nullptr)
	{
		UE_LOG(LogMultiMapPlugin, Fatal, TEXT("Failed to load package '%s'"), *URL.Map);
		return nullptr;
	}

	NewWorld = UWorld::FindWorldInPackage(WorldPackage);

	if (NewWorld == nullptr)
	{
		UE_LOG(LogMultiMapPlugin, Fatal, TEXT("Failed to load package '%s'"), *URL.Map);
		return nullptr;
	}

	NewWorld->PersistentLevel->HandleLegacyMapBuildData();

	FScopeCycleCounterUObject MapScope(WorldPackage);

	//Todo PIE loader

	NewWorld->SetGameInstance(Context->OwningGameInstance);
	Context->SetCurrentWorld(NewWorld);
	Context->World()->WorldType = Context->WorldType;

	if (!Context->World()->bIsWorldInitialized)
	{
		Context->World()->InitWorld();
	}

	//Context->World()->SetGameMode(URL); //Issue #2

	//Todo Networking

	if (GShaderCompilingManager)
	{
		GShaderCompilingManager->ProcessAsyncResults(false, true);
	}

	check(Context->World()->PersistentLevel);

	GEngine->LoadPackagesFully(Context->World(), FULLYLOAD_Map, Context->World()->PersistentLevel->GetOutermost()->GetName());
	Context->World()->FlushLevelStreaming(EFlushLevelStreamingType::Visibility);

	if (!GIsEditor && !IsRunningDedicatedServer())
	{
		// If requested, duplicate dynamic levels here after the source levels are created.
		Context->World()->DuplicateRequestedLevels(FName(*URL.Map));
	}

	Context->World()->CreateAISystem();
	Context->World()->InitializeActorsForPlay(URL);
	UNavigationSystem::InitializeForWorld(Context->World(), FNavigationSystemRunMode::GameMode);

	Context->LastURL = URL;
	Context->LastURL.Map = URL.Map;

//	GEngine->XRSystem->OnBeginPlay(*Context); //Issue #4 (May be not need at all?)
	Context->World()->BeginPlay();

	return Context->World();
}