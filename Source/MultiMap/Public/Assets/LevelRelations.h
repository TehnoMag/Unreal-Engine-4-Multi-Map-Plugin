// Copyright Mickail `TehnoMag` Lukianov © 2018

#pragma once

#include "CoreMinimal.h"
#include "Object.h"
#include "Engine/World.h"
#include "LevelRelations.generated.h"

/**
 * Comment
 */
UENUM()
enum ELevelRelationMethod
{
	/* One map, one port */
	LR_Default	UMETA(DisplayName = "Default"), 
	/* Many maps, one port */
	LR_Proxy	UMETA(DisplayName = "Proxy") 

};

/**
 * Comment
 */
USTRUCT()
struct FLevelContainer
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
		FString LevelName;

	FWorldContext* WorldContext;
	bool bIsLoaded;
	bool bIsActive;

};


/**
 * Comment
 */
USTRUCT(BlueprintType)
struct FLevelRelation
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
		FLevelContainer RootLevel;

	UPROPERTY(EditAnywhere)
		TArray <FLevelContainer> ChildLevels;

};


/**
 *Comment
 */
UCLASS()
class MULTIMAP_API ULevelRelations : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "MultiMapPlugin")
		static bool LoadSubLevel(ULevelRelations* LevelRelations, const FString& LevelName);

	UFUNCTION(BlueprintCallable, Category = "MultiMapPlugin")
		static bool LoadAllSubLevels(ULevelRelations* LevelRelations);

protected:

private:
	UPROPERTY(EditDefaultsOnly)
		TEnumAsByte <ELevelRelationMethod> Method;

	UPROPERTY(EditDefaultsOnly)
		TArray <FLevelRelation> LevelTree;

	int32 FindRelation(const FString& LevelName);
	int32 FindContainer(const int32& RelId, const FString& LevelName);
	
	UWorld* LoadLevel(FWorldContext* Context, const FString& Name);
};

