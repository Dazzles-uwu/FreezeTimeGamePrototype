// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DaffaBuckleyA3 : ModuleRules
{
	public DaffaBuckleyA3(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
