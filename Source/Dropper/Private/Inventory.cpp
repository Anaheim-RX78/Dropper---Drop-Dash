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
	// Find the slot for the given item in the inventory and increase di amount.
	if (FSlot* SlotPtr = GetSlotByData(Item))
	{
		SlotPtr->Amount += Amount;
	}
	// If no slot is found, create one and add it into the inventory.
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
void UInventory::AddItem(AItemActor* Item, const int Amount)
{
	// Add the item into the inventory
	AddItem(Item->Data, Amount);

	// Destroy the spawned item
	Item->Destroy();
}

/**
 * Remove an item from the inventory
 * @param Item Item to be removed
 * @param Amount Quantity of items to be removed
 * @param Location Location to be placed the dropped items
 */
void UInventory::DropItem(const UItemData* Item, const int Amount, const FVector& Location) const
{
	for (int i = 0; i < Amount; i++)
	{
		// For each item in the inventory, spawn it in the defined location.
		GetWorld()->SpawnActor<AItemActor>(Item->Item, Location, FRotator::ZeroRotator);
	}
}

/**
 * Remove an item from the inventory
 * @param Index Index of the item to be removed
 * @param Amount Quantity of items to be removed
 * @param Location Location to be placed the dropped items
 */
void UInventory::DropItem(const int Index, const int Amount, const FVector& Location)
{
	// Drop the item based on the slot index
	DropItem(Slots[Index].Data, Amount, Location);
}

/**
 * Get the single inventory slot based on the item data
 * @param Item Item data
 * @return Inventory slot
 */
FSlot* UInventory::GetSlotByData(const UItemData* Item)
{
	// Loop through the inventory slots, if the slot contains the item, return the slot.
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
