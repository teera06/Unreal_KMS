// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Unreal_Project : ModuleRules
{
	public Unreal_Project(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicIncludePaths.Add(System.IO.Path.Combine(ModuleDirectory, ""));

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "NavigationSystem", "Paper2D" });

        //PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
