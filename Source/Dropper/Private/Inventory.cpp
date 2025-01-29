// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

/**
 * Sets default values for this component's properties
 */
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame. You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

/**
 * Called when the game starts
 */
void UInventory::BeginPlay()
{
	Super::BeginPlay();
}

/**
 * Add an item into the inventory
 * @param Item Item type
 * @param Amount Quantity of items to be added
 */
void UInventory::AddItem(UItemData* Item, const int Amount)
{
	if (FSlot* SlotPtr = GetSlotByData(Item))
	{
		SlotPtr->Amount += Amount;
	}
	else
	{
		FSlot Slot;
		Slot.Data = Item;
		Slot.Amount = Amount;
		Slots.Add(Slot);
	}
}

/**
 * Add an item into the inventory
 * @param Item Item
 * @param Amount Quantity of items to be added
 */
void UInventory::AddItem(AItemActor* Item, int Amount)
{
}

/**
 * Remove an item from the inventory
 * @param Item Item to be removed
 * @param Amount Quantity of items to be removed
 * @param Location Location to be placed the dropped items
 */
void UInventory::DropItem(UItemData* Item, int Amount, FVector Location)
{
}

/**
 * Remove an item from the inventory
 * @param Index Index of the item to be removed
 * @param Amount Quantity of items to be removed
 * @param Location Location to be placed the dropped items
 */
void UInventory::DropItem(int Index, int Amount, FVector Location)
{
}

/**
 * Get the single inventory slot based on the item data
 * @param Item Item data
 * @return Inventory slot
 */
FSlot* UInventory::GetSlotByData(const UItemData* Item)
{
	for (FSlot& Slot : Slots)
	{
		if (Slot.Data == Item)
		{
			return &Slot;
		}
	}

	return nullptr;
}


/**
 * Called every frame
 */
void UInventory::TickComponent(const float DeltaTime, const ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
