// Copyright shenkns Inventory System Developed With Unreal Engine. All Rights Reserved 2023.

#pragma once

#include "Data/Data.h"

#include "InventoryItemData.generated.h"

class UInventoryItem;

UCLASS()
class INVENTORYSYSTEM_API UInventoryItemData : public UData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	TSubclassOf<UInventoryItem> ItemClass;
};
