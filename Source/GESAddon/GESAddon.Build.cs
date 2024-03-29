﻿// Copyright (C) 2024 owoDra

using UnrealBuildTool;

public class GESAddon : ModuleRules
{
	public GESAddon(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[]
            {
                ModuleDirectory,
                ModuleDirectory + "/GESAddon",
            }
        );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "GameplayTags",
                "GameplayAbilities",
                "UMG",
            }
        );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "GFCore",
                "GAExt",
                "GAEAddon",
            }
        );
    }
}
