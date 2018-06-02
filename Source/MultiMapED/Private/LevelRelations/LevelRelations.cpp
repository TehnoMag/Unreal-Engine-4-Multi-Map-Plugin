// Copyright Mickail `TehnoMag` Lukianov © 2018

#include "LevelRelations_Factory.h"
#include "LevelRelations.h"

ULevelRelations_Factory::ULevelRelations_Factory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = ULevelRelations::StaticClass();
}

UObject* ULevelRelations_Factory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<ULevelRelations>(InParent, InName, Flags | RF_Transactional);
}

FText FLevelRelations_Actions::GetName() const
{
	return FText::FromString("Levels Relation");
}

UClass* FLevelRelations_Actions::GetSupportedClass() const
{
	return ULevelRelations::StaticClass();
}

FColor FLevelRelations_Actions::GetTypeColor() const
{
	return FColor::Blue;
}

uint32 FLevelRelations_Actions::GetCategories()
{
	return EAssetTypeCategories::Basic | Category;
}