// Copyright Mickail `TehnoMag` Lukianov © 2018

#include "MultiMapGameInstance.h"
#include "Engine/Engine.h"

UWorld* UMultiMapGameInstance::GetWorld() const
{
	return CurrentSubWorldContext ? CurrentSubWorldContext->World() :
		WorldContext ? WorldContext->World() : NULL;
}

void UMultiMapGameInstance::SetSubWorldContext(FWorldContext* WorldContext)
{
	CurrentSubWorldContext = WorldContext;
}

void UMultiMapGameInstance::ResetSubWorldContext()
{
	CurrentSubWorldContext = nullptr;
}