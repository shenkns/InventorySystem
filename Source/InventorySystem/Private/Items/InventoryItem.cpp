// Copyright shenkns Inventory System Developed With Unreal Engine. All Rights Reserved 2023.

#include "Items/InventoryItem.h"

#include "Data/InventoryItemData.h"

UWorld* UInventoryItem::GetWorld() const
{
	return GetOuter() ? GetOuter()->GetWorld() : nullptr;
}

void UInventoryItem::PostInitProperties()
{
	Super::PostInitProperties();

	if(UniqueID.IsEmpty())
	{
		UniqueID = FGuid::NewGuid().ToString();
	}
}

bool UInventoryItem::SetID(FString NewID)
{
	if(NewID != UniqueID)
	{
		UniqueID = NewID;
		return true;
	}

	return false;
}

FName UInventoryItem::GetTag() const
{
	return InventoryData ? InventoryData->Tag : NAME_None;
}