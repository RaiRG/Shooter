// Shooter Game, All Rights Reserved.

using UnrealBuildTool;

public class Shooter : ModuleRules
{
	public Shooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"EnhancedInput",
			"UMG",
			"GameplayTasks",
			"NavigationSystem", 
			"AIModule",
			"GameplayAbilities"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[]
		{
			"Shooter/Public/Player",
			"Shooter/Public/Components",
			"Shooter/Public/Weapon",
			"Shooter/Public/UI",
			"Shooter/Public/AI",
			"Shooter/Public/AI/Tasks",
			"Shooter/Public/AI/Services",
			"Shooter/Public/AI/EQS"
		});
	}
}
