// Copyright Mickail `TehnoMag` Lukianov © 2018

using UnrealBuildTool;

public class MultiMapED : ModuleRules
{
    public MultiMapED ( ReadOnlyTargetRules Target ) : base( Target )
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange( new string[]
        {
            "UnrealED",
            "Core",
            "CoreUObject",
            "MultiMap",
            "Slate",
            "SlateCore",
            "Projects"
        } 
        );
    }
}