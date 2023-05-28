// Copyright shenkns Inventory System Developed With Unreal Engine. All Rights Reserved 2023.

#pragma once

#include "Data/Data.h"

#include "RarityData.generated.h"

UCLASS()
class INVENTORYSYSTEM_API URarityData : public UData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory|Rarity")
	FColor RarityColor = FColor::White;
};
