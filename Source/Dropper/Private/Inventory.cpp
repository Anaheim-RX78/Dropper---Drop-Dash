#include "Inventory.h"

#include "Coin.h"
#include "DropperGameInstance.h"
#include "ItemActor.h"
#include "Kismet/GameplayStatics.h"

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
		InventorySlots.Add(Slot);
	}
}

void UInventory::AddItem(AItemActor* Item, const int Amount)
{
	// Add the item into the inventory
	this->AddItem(Item->Data, Amount);

	// Destroy the spawned item
	Item->Destroy();
}

void UInventory::DropItem(const UItemData* Item, const int Amount, const FVector& Location)
{
	const bool IsACoin = Item->Item->IsChildOf(ACoin::StaticClass());
	UDropperGameInstance* DropperInstance = Cast<UDropperGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!IsValid(DropperInstance))
	{
		// GameInstance is not an instance of DropperGameInstance, display an error message
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
		                                 "GameInstance is not an instance of DropperGameInstance");
		return;
	}

	FSlot* Slot = GetSlotByData(Item);
	if (Slot->Amount > Amount)
	{
		// If there is enough amount, decrease the amount in the inventory.
		Slot->Amount -= Amount;
		if (IsACoin)
		{
			DropperInstance->TotalCoins -= Amount;
		}
	}
	else
	{
		// If there is not enough amount, remove all items from the inventory.
		Slot->Amount = 0;
		if (IsACoin)
		{
			DropperInstance->TotalCoins = 0;
		}
	}

	for (int i = 0; i < Amount; i++)
	{
		// For each item in the inventory, spawn it in the defined location.
		this->GetWorld()->SpawnActor<AItemActor>(Item->Item, Location, FRotator::ZeroRotator);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "Item dropped");
	}
}

void UInventory::DropItem(const int Index, const int Amount, const FVector& Location)
{
	// Drop the item based on the slot index
	this->DropItem(InventorySlots[Index].Data, Amount, Location);
}

void UInventory::ClearInventory()
{
	for (int Index = 0; Index < this->InventorySlots.Num(); Index++)
	{
		this->InventorySlots.RemoveAt(Index);
	}

	UGameInstance* Instance = UGameplayStatics::GetGameInstance(GetWorld());
	UDropperGameInstance* DropperInstance = Cast<UDropperGameInstance>(Instance);

	if (IsValid(DropperInstance))
	{
		DropperInstance->TotalCoins = 0;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
		                                 "The game instance is not an instance of UDropperGameInstance");
		return;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "Inventory cleared");
}

FSlot* UInventory::GetSlotByData(const UItemData* Item)
{
	// Loop through the inventory slots, if the slot contains the item, return the slot.
	for (FSlot& Slot : InventorySlots)
	{
		if (Slot.Data == Item)
		{
			return &Slot;
		}
	}

	return nullptr;
}

FSlot* UInventory::GetSlotByIndex(const int Index)
{
	if (this->InventorySlots.IsEmpty() || Index > this->InventorySlots.Num())
	{
		return nullptr;
	}

	return &InventorySlots[Index];
}

void UInventory::ScrollInventory()
{
	if (this->InventorySlots.IsEmpty())
	{
		return;
	}

	if (this->CurrentSlotIndex + 2 > this->InventorySlots.Num())
	{
		this->CurrentSlotIndex = 0;
	}
	else
	{
		this->CurrentSlotIndex++;
	}

	const FSlot* CurrentSlot = this->GetSlotByIndex(this->CurrentSlotIndex);
	if (CurrentSlot->Amount == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Inventory slot empty");
	}
	else
	{
		const FString Message = FString::Printf(TEXT("Selected item: %s - %s"), *CurrentSlot->Data->Name,
		                                        *CurrentSlot->Data->Description);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Message);
	}
}

void UInventory::TickComponent(const float DeltaTime, const ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction)
{
	this->Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
