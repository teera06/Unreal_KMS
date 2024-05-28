// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Unreal_Project : ModuleRules
{
	public Unreal_Project(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
