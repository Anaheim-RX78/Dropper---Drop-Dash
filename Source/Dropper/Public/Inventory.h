// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

/**
 * Struct to determine each slot of the inventory
 */
USTRUCT()
struct FSlot
{
	GENERATED_BODY()

	/**
	 * How many items the inventory contains for the same type
	 */
	UPROPERTY(EditAnywhere, Category=Item)
	int Amount;

	/**
	 * Item reference
	 */
	UPROPERTY(EditAnywhere, Category=Item)
	UItemData* Data;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPPER_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:
	/**
	 * Sets default values for this component's properties
	 */
	UInventory();

protected:
	/**
	 * Array of slots—Container for items
	 */
	UPROPERTY(EditAnywhere, Category=Inventory)
	TArray<FSlot> Slots;

	/**
	 * Called when the game starts
	 */
	virtual void BeginPlay() override;

public:
	/**
	 * Add an item into the inventory
	 * @param Item Item type
	 * @param Amount Quantity of items to be added
	 */
	void AddItem(UItemData* Item, int Amount);

	/**
	 * Add an item into the inventory
	 * @param Item Item
	 * @param Amount Quantity of items to be added
	 */
	void AddItem(AItemActor* Item, int Amount);

	/**
	 * Remove an item from the inventory
	 * @param Item Item to be removed
	 * @param Amount Quantity of items to be removed
	 * @param Location Location to be placed the dropped items
	 */
	void DropItem(UItemData* Item, int Amount, FVector Location);

	/**
	 * Remove an item from the inventory
	 * @param Index Index of the item to be removed
	 * @param Amount Quantity of items to be removed
	 * @param Location Location to be placed the dropped items
	 */
	void DropItem(int Index, int Amount, FVector Location);

	/**
	 * Get the single inventory slot based on the item data
	 * @param Item Item data
	 * @return Inventory slot
	 */
	FSlot* GetSlotByData(const UItemData* Item);

	/**
	 * Called every frame
	 */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
