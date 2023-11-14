// Copyright shenkns Inventory System Developed With Unreal Engine. All Rights Reserved 2023.

#include "Stats/StatInventory.h"

#include "Log.h"
#include "Log/Details/LocalLogCategory.h"
#include "Managers/StatsManager.h"
#include "Module/InventorySystemModule.h"

DEFINE_LOG_CATEGORY_LOCAL(LogInventorySystem);

bool UStatInventory::PreConvertToSaveData_Implementation()
{
	// Serialize Items
	if(!USerializationSystemLibrary::ConvertObjectsToSaveData<UInventoryItem>(Items, ItemsSaveData)) return false;

	return true;
}

bool UStatInventory::PostConvertFromSaveData_Implementation()
{
	// Load Inventory Items
	Items = USerializationSystemLibrary::ConvertSaveDataToObjects<UInventoryItem>(ItemsSaveData, this);

	return true;
}

bool UStatInventory::AddItem(UInventoryItem* Item)
{
	if(!Item) return false;

	// Reinit Item For Inventory
	Item->Rename(nullptr, this);
	Items.Add(Item);

	LOG(Display, "{} Added To Inventory", *Item->GetName());
	
	GetManager()->SaveStats();
	OnItemAdded.Broadcast(Item);

	return true;
}

UInventoryItem* UStatInventory::DuplicateAndAddItem(const UInventoryItem* Item)
{
	if(!IsValid(Item)) return nullptr;

	UInventoryItem* NewItem = DuplicateObject<UInventoryItem>(Item, this);
	NewItem->SetID(FGuid::NewGuid().ToString());
	
	// Try To Add
	if(AddItem(NewItem)) return NewItem;
	return nullptr;
}

bool UStatInventory::RemoveItem(UInventoryItem* Item)
{
	if(!Item) return false;

	// Try To Remove
	if(Items.Remove(Item) > 0)
	{
		LOG(Display, "{} Removed From Inventory", *Item->GetName());
		
		GetManager()->SaveStats();
		OnItemRemoved.Broadcast(Item);
		return true;
	}

	return false;
}

bool UStatInventory::ClearItems()
{
	bool AllRemoved = true;
	// Iterate Items And Remove Them
	for(int i = Items.Num() - 1;  i >= 0; i--)
	{
		if(!RemoveItem(Items[i])) AllRemoved = false;;
	}

	LOG(Display, "Inventory Items Cleared");

	return AllRemoved;
}

TArray<UInventoryItem*> UStatInventory::GetInventoryItems(TSubclassOf<UInventoryItem> Class) const
{
	if(!Class) Class = UInventoryItem::StaticClass();

	return Items.FilterByPredicate([Class](const UInventoryItem* Src)
	{
		return Src && Src->GetClass()->IsChildOf(Class);
	});
}

TArray<UInventoryItem*> UStatInventory::GetInventoryItemsWithTag(TSubclassOf<UInventoryItem> Class, FName Tag) const
{
	if(!Class) Class = UInventoryItem::StaticClass();
	
	return Items.FilterByPredicate([Class, Tag](const UInventoryItem* Src)
	{
		return Src && Src->GetClass()->IsChildOf(Class) && Src->GetTag() == Tag;
	});
}

UInventoryItem* UStatInventory::GetInventoryItemWithID(TSubclassOf<UInventoryItem> Class, FString ID) const
{
	if(!Class) Class = UInventoryItem::StaticClass();
	
	UInventoryItem* const* Item = Items.FindByPredicate([Class, ID](const UInventoryItem* Src)
	{
		return Src && Src->GetClass()->IsChildOf(Class) && Src->GetID() == ID;
	});

	return Item ? *Item : nullptr;
}
