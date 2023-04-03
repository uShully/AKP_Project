// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AKP_Project : ModuleRules
{
	public AKP_Project(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" , "UMG", "NavigationSystem", "AIModule", "GameplayTasks"});
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
	}
}
