// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UnrealProgramGame : ModuleRules
{
	public UnrealProgramGame(ReadOnlyTargetRules Target) : base(Target)
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
			"Slate",
			"MetasoundEngine",
			"Niagara",
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { "OpenSubdiv" });

		PublicIncludePaths.AddRange(new string[] {
			"UnrealProgramGame",
			"UnrealProgramGame/Variant_Horror",
			"UnrealProgramGame/Variant_Horror/UI",
			"UnrealProgramGame/Variant_Shooter",
			"UnrealProgramGame/Variant_Shooter/AI",
			"UnrealProgramGame/Variant_Shooter/UI",
			"UnrealProgramGame/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
