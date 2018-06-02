// Copyright Mickail `TehnoMag` Lukianov © 2018

#pragma once

#include "ModuleManager.h"
#include "SlateStyle.h"

class FMultiMapEDModuleImpl : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TSharedPtr <FSlateStyleSet> StyleSet;
};