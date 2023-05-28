// Copyright shenkns Inventory System Developed With Unreal Engine. All Rights Reserved 2023.

#pragma once

#include "UObject/Object.h"

#include "InventoryItem.generated.h"

class UInventoryItemData;

UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class INVENTORYSYSTEM_API UInventoryItem : public UObject
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Inventory")
	UInventoryItemData* InventoryData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory", meta = (ExposeOnSpawn = true))
	FString UniqueID;

public:

	virtual UWorld* GetWorld() const override;

	virtual void PostInitProperties() override;

	UFUNCTION(BlueprintCallable, Category = "Inventory", meta = (CompactNodeTitle = "ID"))
	bool SetID(FString NewID);

	// Item Stats Getters
	UFUNCTION(BlueprintPure, Category = "Inventory", meta = (CompactNodeTitle = "Data", DeterminesOutputType = "Class"))
	UInventoryItemData* GetInventoryData(TSubclassOf<UInventoryItemData> Class) const { return InventoryData; };

	UFUNCTION(BlueprintPure, Category = "Inventory", meta = (CompactNodeTitle = "Tag"))
	FName GetTag() const;
	
	UFUNCTION(BlueprintPure, Category = "Inventory", meta = (CompactNodeTitle = "ID"))
	FString GetID() const { return UniqueID; };

	template<typename T>
	T* GetInventoryData() const;
};

template <typename T>
T* UInventoryItem::GetInventoryData() const
{
	return InventoryData ? static_cast<T*>(InventoryData) : nullptr;
}
