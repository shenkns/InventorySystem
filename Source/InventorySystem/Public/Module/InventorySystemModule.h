// Copyright shenkns Inventory System Developed With Unreal Engine. All Rights Reserved 2023.

#pragma once

#include "Modules/ModuleManager.h"

INVENTORYSYSTEM_API DECLARE_LOG_CATEGORY_EXTERN(LogInventorySystem, Log, All);

class FInventorySystemModule : public IModuleInterface
{
public:

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
private:

#if UE_EDITOR
	void RegisterSystemSettings() const;
	void UnregisterSystemSettings() const;
#endif
};
