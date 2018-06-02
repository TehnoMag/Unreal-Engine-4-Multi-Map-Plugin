// Copyright Mickail `TehnoMag` Lukianov © 2018

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MultiMapGameInstance.generated.h"

/**
 *Comment
 */
UCLASS()
class MULTIMAP_API UMultiMapGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual class UWorld* GetWorld() const override;
	void SetSubWorldContext(FWorldContext* WorldContext);
	void ResetSubWorldContext();

protected:

private:
	FWorldContext* CurrentSubWorldContext;

};
