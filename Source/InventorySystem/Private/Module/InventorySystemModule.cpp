// Copyright shenkns Inventory System Developed With Unreal Engine. All Rights Reserved 2023.

#include "Module/InventorySystemModule.h"

#if UE_EDITOR
#include "ISettingsModule.h"
#include "Module/InventorySystemSettings.h"
#endif

IMPLEMENT_MODULE(FInventorySystemModule, InventorySystem);

INVENTORYSYSTEM_API DEFINE_LOG_CATEGORY(LogInventorySystem);

void FInventorySystemModule::StartupModule()
{
#if UE_EDITOR
	RegisterSystemSettings();
#endif
}

void FInventorySystemModule::ShutdownModule()
{
#if UE_EDITOR
	UnregisterSystemSettings();
#endif
}

#if UE_EDITOR
void FInventorySystemModule::RegisterSystemSettings() const
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings(
			"Project",
			"Plugins",
			"Inventory System",
			FText::FromString(TEXT("Inventory System")),
			FText::FromString(TEXT("Configuration settings for Inventory System")),
			GetMutableDefault<UInventorySystemSettings>()
		);
	}
}

void FInventorySystemModule::UnregisterSystemSettings() const
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "Inventory System");
	}
}
#endif
