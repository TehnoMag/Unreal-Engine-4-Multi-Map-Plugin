// Copyright Mickail `TehnoMag` Lukianov © 2018

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "AssetTypeActions_Base.h"
#include "LevelRelations_Factory.generated.h"

class FLevelRelations_Actions : public FAssetTypeActions_Base
{
public:
	virtual FText GetName() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual FColor GetTypeColor() const override;
	virtual uint32 GetCategories() override;

	virtual class UThumbnailInfo* GetThumbnailInfo(UObject* Asset) const override { return nullptr; };

	static uint32 Category;
};

/**
 *Comment
 */
UCLASS()
class ULevelRelations_Factory : public UFactory
{
	GENERATED_BODY()

public:
	ULevelRelations_Factory();
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

protected:

private:

};

