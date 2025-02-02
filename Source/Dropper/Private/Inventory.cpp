#include "Inventory.h"
#include "ItemActor.h"

UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame. You can turn these features
	// off to improve performance if you don't need them.
	this->PrimaryComponentTick.bCanEverTick = true;
}

void UInventory::BeginPlay()
{
	this->Super::BeginPlay();
}

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

void UInventory::AddItem(AItemActor* Item, const int Amount)
{
	// Add the item into the inventory
	this->AddItem(Item->Data, Amount);
	const FString Message = FString::Printf(TEXT("There are %d items in the inventory"),
	                                        this->GetSlotByData(Item->Data)->Amount);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, Message);

	// Destroy the spawned item
	Item->Destroy();
}

void UInventory::DropItem(const UItemData* Item, const int Amount, const FVector& Location) const
{
	for (int i = 0; i < Amount; i++)
	{
		// For each item in the inventory, spawn it in the defined location.
		this->GetWorld()->SpawnActor<AItemActor>(Item->Item, Location, FRotator::ZeroRotator);
	}
}

void UInventory::DropItem(const int Index, const int Amount, const FVector& Location)
{
	// Drop the item based on the slot index
	this->DropItem(Slots[Index].Data, Amount, Location);
}

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

void UInventory::TickComponent(const float DeltaTime, const ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction)
{
	this->Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
