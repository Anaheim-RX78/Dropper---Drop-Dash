// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemActor.h"
#include "Engine/DataAsset.h"
#include "ItemData.generated.h"

/**
 * 
 */
UCLASS()
class DROPPER_API UItemData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category=Item)
	FString Name;

	UPROPERTY(EditAnywhere, Category=Item)
	FString Description;

	UPROPERTY(EditAnywhere, Category = Item)
	TSubclassOf<AItemActor> Item;
};
