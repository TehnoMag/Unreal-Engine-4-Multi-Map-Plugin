// Copyright Mickail `TehnoMag` Lukianov © 2018

#include "MultiMapED.h"
#include "IPluginManager.h"
#include "SlateStyleRegistry.h"
#include "Private/LevelRelations/LevelRelations_Factory.h"

uint32 FLevelRelations_Actions::Category = 0;

void FMultiMapEDModuleImpl::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	AssetTools.RegisterAssetTypeActions(MakeShareable(new FLevelRelations_Actions));
	FLevelRelations_Actions::Category = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("TehnoMag_Assets")), FText::FromString("TehnoMag`s Assets"));

	StyleSet = MakeShareable(new FSlateStyleSet("MultiMapStyle"));

	const FString ContentDir = IPluginManager::Get().FindPlugin("MultiMap")->GetBaseDir();
	StyleSet->SetContentRoot(ContentDir);

	FSlateImageBrush* ThumbBrush = new FSlateImageBrush(
		StyleSet->RootToContentDir(TEXT("Resources/LevelRelations_64x"), TEXT(".png")),
		FVector2D(64.f, 64.f)
	);

	if (ThumbBrush)
	{
		StyleSet->Set("ClassThumbnail.LevelRelations", ThumbBrush);
		FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
	}
}

void FMultiMapEDModuleImpl::ShutdownModule()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(StyleSet->GetStyleSetName());
}

IMPLEMENT_MODULE(FMultiMapEDModuleImpl, MultiMapED);