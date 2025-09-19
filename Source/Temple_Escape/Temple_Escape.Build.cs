// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Temple_Escape : ModuleRules
{
	public Temple_Escape(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Temple_Escape",
			"Temple_Escape/Variant_Platforming",
			"Temple_Escape/Variant_Platforming/Animation",
			"Temple_Escape/Variant_Combat",
			"Temple_Escape/Variant_Combat/AI",
			"Temple_Escape/Variant_Combat/Animation",
			"Temple_Escape/Variant_Combat/Gameplay",
			"Temple_Escape/Variant_Combat/Interfaces",
			"Temple_Escape/Variant_Combat/UI",
			"Temple_Escape/Variant_SideScrolling",
			"Temple_Escape/Variant_SideScrolling/AI",
			"Temple_Escape/Variant_SideScrolling/Gameplay",
			"Temple_Escape/Variant_SideScrolling/Interfaces",
			"Temple_Escape/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
