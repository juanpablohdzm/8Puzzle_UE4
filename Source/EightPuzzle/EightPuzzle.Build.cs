// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EightPuzzle : ModuleRules
{
	public EightPuzzle(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay","TweenMaker" });
	}
}
