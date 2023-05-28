// Copyright shenkns Inventory System Developed With Unreal Engine. All Rights Reserved 2023.

using UnrealBuildTool;

public class InventorySystem : ModuleRules
{
	public InventorySystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PrivateIncludePaths.AddRange(
			new string[] {
				"InventorySystem/Public/"
			}
		);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"LogSystem",
				"ManagersSystem",
				"DataSystem",
				"SerializationSystem",
				"SaveLoadSystem"
			}
		);
		
		PrivateIncludePathModuleNames.AddRange(
			new string[]
			{
				"LogSystem",
				"ManagersSystem",
				"DataSystem",
				"SerializationSystem",
				"SaveLoadSystem"		
			}
		);
	}
}
