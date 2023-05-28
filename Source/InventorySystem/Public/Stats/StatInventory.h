// Copyright shenkns Inventory System Developed With Unreal Engine. All Rights Reserved 2023.

#pragma once

#include "Stats/Stat.h"
#include "Interfaces/SerializationInterface.h"

#include "Libs/SerializationSystemLibrary.h"
#include "Items/InventoryItem.h"

#include "StatInventory.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryItemEvent, UInventoryItem*, Item);

UCLASS()
class INVENTORYSYSTEM_API UStatInventory : public UStat, public ISerializationInterface
{
	GENERATED_BODY()

	public:

	UPROPERTY(BlueprintAssignable, Category = "Profile|Inventory")
	FInventoryItemEvent OnItemAdded;

	UPROPERTY(BlueprintAssignable, Category = "Profile|Inventory")
	FInventoryItemEvent OnItemRemoved;

protected:

	UPROPERTY(EditDefaultsOnly, Instanced, Category = "Profile|Stats|Inventory")
	TArray<UInventoryItem*> Items;

	UPROPERTY()
	TArray<FObjectSaveData> ItemsSaveData;

public:
	// Manage Items
	UFUNCTION(BlueprintCallable, Category = "Profile|Inventory", meta = (CompactNodeTitle = "Add"))
	bool AddItem(UInventoryItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Profile|Inventory", meta = (CompactNodeTitle = "Duplicate"))
	UInventoryItem* DuplicateAndAddItem(const UInventoryItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Profile|Inventory", meta = (CompactNodeTitle = "Remove"))
	bool RemoveItem(UInventoryItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Profile|Inventory", meta = (CompactNodeTitle = "Clear"))
	bool ClearItems();

	// Items Getters
	UFUNCTION(BlueprintPure, Category = "Profile|Inventory", meta = (CompactNodeTitle = "Items", DeterminesOutputType = "Class"))
	TArray<UInventoryItem*> GetInventoryItems(TSubclassOf<UInventoryItem> Class) const;

	UFUNCTION(BlueprintPure, Category = "Profile|Inventory", meta = (CompactNodeTitle = "Items", DeterminesOutputType = "Class"))
	TArray<UInventoryItem*> GetInventoryItemsWithTag(TSubclassOf<UInventoryItem> Class, FName Tag) const;

	UFUNCTION(BlueprintPure, Category = "Profile|Inventory", meta = (CompactNodeTitle = "Item", DeterminesOutputType = "Class"))
	UInventoryItem* GetInventoryItemWithID(TSubclassOf<UInventoryItem> Class, FString ID) const;

	template<typename T>
	TArray<T*> GetInventoryItems() const;

	template<typename T>
	TArray<T*> GetInventoryItemsWithTag(FName Tag) const;

	template<typename T>
	T* GetInventoryItemWithID(FString ID) const;
	
	// Serialization
	virtual bool PreConvertToSaveData_Implementation() override;
	virtual bool PostConvertFromSaveData_Implementation() override;
};

template <typename T>
TArray<T*> UStatInventory::GetInventoryItems() const
{
	const TArray<UInventoryItem*> Out = Items.FilterByPredicate([&](const UInventoryItem* Src)
	{
		return Src && Src->GetClass()->IsChildOf(T::StaticClass());
	});

	return reinterpret_cast<TArray<T*>&>(Out);
}

template <typename T>
TArray<T*> UStatInventory::GetInventoryItemsWithTag(FName Tag) const
{
	const TArray<UInventoryItem*> Out = Items.FilterByPredicate([Tag](const UInventoryItem* Src)
	{
		return Src && Src->GetClass()->IsChildOf(T::StaticClass()) && Src->GetTag() == Tag;
	});

	return reinterpret_cast<TArray<T*>&>(Out);
}

template <typename T>
T* UStatInventory::GetInventoryItemWithID(FString ID) const
{
	UInventoryItem* const* Out = Items.FindByPredicate([ID](const UInventoryItem* Src)
	{
		return Src && Src->GetClass()->IsChildOf(T::StaticClass()) && Src->GetID() == ID;
	});

	return Out ? static_cast<T*>(*Out) : nullptr;
}
