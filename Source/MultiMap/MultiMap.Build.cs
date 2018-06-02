// Copyright Mickail `TehnoMag` Lukianov © 2018

using UnrealBuildTool;

public class MultiMap : ModuleRules
{
	public MultiMap( ReadOnlyTargetRules Target ) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange ( new string[] { "Engine", "Core", "CoreUObject" } );
	}	
}