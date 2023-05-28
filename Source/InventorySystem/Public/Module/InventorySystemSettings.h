// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/Object.h"

#include "InventorySystemSettings.generated.h"

UCLASS(Config=Game, DefaultConfig)
class INVENTORYSYSTEM_API UInventorySystemSettings : public UObject
{
	GENERATED_BODY()
	
public:

	// Debug
	UPROPERTY(EditDefaultsOnly, Config, Category = "Debug")
	bool bShowDebugMessages;
};
