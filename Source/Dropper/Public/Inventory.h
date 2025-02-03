#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"

/**
 * @brief Struct to determine each slot of the inventory.
 *
 * This struct represents a single slot in the inventory, containing information
 * about the item type and the quantity of that item in the slot.
 */
USTRUCT()
struct FSlot
{
	GENERATED_BODY()

	/**
	 * @brief The quantity of items of the same type in this inventory slot.
	 *
	 * This property represents the number of items that are stored in this particular
	 * inventory slot. It is used to keep track of how many items of the same type
	 * are currently held in the slot. For example, if the slot contains health potions,
	 * this property will indicate how many health potions are in the slot.
	 */
	UPROPERTY(EditAnywhere, Category=Item)
	int Amount;

	/**
	 * @brief Reference to the item data associated with this slot.
	 *
	 * This property holds a reference to the `UItemData` object that represents the type of item
	 * stored in this inventory slot. It is used to identify the item type and access its properties,
	 * such as name, description, and other relevant data.
	 */
	UPROPERTY(EditAnywhere, Category=Item)
	UItemData* Data;
};

/**
 * @brief Inventory component for managing items.
 *
 * This class represents an inventory component that can be attached to an actor.
 * It provides functionality to add, remove, and manage items within the inventory.
 * The inventory is composed of slots, each containing a specific type of item and its quantity.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPPER_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:
	/**
	 * @brief Sets default values for this component's properties.
	 *
	 * This constructor initializes the inventory component with default values.
	 * It sets up any necessary properties or configurations required for the inventory
	 * to function correctly when the game starts or when the component is spawned.
	 */
	UInventory();

protected:
	/**
	 * @brief Array of slots—Container for items.
	 *
	 * This property represents the inventory slots, each containing a specific type of item and its quantity.
	 * It is used to manage and organize the items held by the inventory component.
	 */
	UPROPERTY(EditAnywhere, Category=Inventory)
	TArray<FSlot> InventorySlots;

	/**
	 * @brief Called when the game starts or when spawned.
	 *
	 * This function is called when the game starts or when the component is spawned.
	 * It is used to initialize any properties or perform any setup required for the inventory
	 * component to function correctly during gameplay.
	 */
	virtual void BeginPlay() override;

public:
	/**
	 * @brief The index of the current slot in the inventory.
	 *
	 * This property represents the index of the currently selected slot in the inventory.
	 * It is used to keep track of which slot is currently active or selected by the player.
	 */
	UPROPERTY(VisibleAnywhere, Category=Inventory)
	int CurrentSlotIndex = 0;

	/**
	 * @brief Add an item into the inventory.
	 *
	 * This function adds a specified quantity of a given item type to the inventory.
	 * If the item already exists in the inventory, the quantity is increased.
	 * Otherwise, a new slot is created for the item.
	 *
	 * @param Item The item type to be added.
	 * @param Amount The quantity of the item to be added.
	 */
	void AddItem(UItemData* Item, int Amount);

	/**
	 * @brief Add an item into the inventory.
	 *
	 * This function adds a specified quantity of a given item actor to the inventory.
	 * If the item already exists in the inventory, the quantity is increased.
	 * Otherwise, a new slot is created for the item.
	 *
	 * @param Item The item actor to be added.
	 * @param Amount The quantity of the item to be added.
	 */
	void AddItem(AItemActor* Item, int Amount);

	/**
	 * @brief Remove an item from the inventory.
	 *
	 * This function removes a specified quantity of a given item type from the inventory.
	 * If the quantity to be removed is greater than the quantity in the inventory, all items of that type are removed.
	 * The removed items are spawned at the specified location in the game world.
	 *
	 * @param Item The item type to be removed.
	 * @param Amount The quantity of the item to be removed.
	 * @param Location The location where the removed items will be spawned.
	 */
	void DropItem(const UItemData* Item, int Amount, const FVector& Location);

	/**
	 * @brief Remove an item from the inventory by index.
	 *
	 * This function removes a specified quantity of an item from the inventory based on its index.
	 * If the quantity to be removed is greater than the quantity in the inventory, all items of that type are removed.
	 * The removed items are spawned at the specified location in the game world.
	 *
	 * @param Index The index of the item to be removed.
	 * @param Amount The quantity of the item to be removed.
	 * @param Location The location where the removed items will be spawned.
	 */
	void DropItem(int Index, int Amount, const FVector& Location);

	/**
	 * @brief Clear all items from the inventory.
	 *
	 * This function removes all items from the inventory, effectively resetting it to an empty state.
	 * It clears all slots and their associated item data, making the inventory ready for new items to be added.
	 */
	void ClearInventory();

	/**
	 * @brief Get the single inventory slot based on the item data.
	 *
	 * This function searches through the inventory slots to find a slot that contains the specified item data.
	 * If a matching slot is found, it returns a pointer to that slot. If no matching slot is found, it returns nullptr.
	 *
	 * @param Item The item data to search for in the inventory slots.
	 * @return A pointer to the inventory slot containing the specified item data, or nullptr if no matching slot is found.
	 */
	FSlot* GetSlotByData(const UItemData* Item);


	/**
	 * @brief Get the single inventory slot based on the index.
	 *
	 * This function retrieves a slot from the inventory based on its index.
	 * It returns a pointer to the slot if the index is valid, or nullptr if the index is out of range.
	 *
	 * @param Index The index of the slot to retrieve.
	 * @return A pointer to the inventory slot at the specified index, or nullptr if the index is invalid.
	 */
	FSlot* GetSlotByIndex(const int Index);

	/**
	 * @brief Called every frame.
	 *
	 * This function is called once per frame and is used to update the inventory component.
	 * It performs any necessary per-frame updates or logic required for the inventory to function correctly.
	 *
	 * @param DeltaTime The time elapsed since the last frame.
	 * @param TickType The type of tick this is, for example, are we paused, or 'simulating' in the editor.
	 * @param ThisTickFunction Internal tick function struct that caused this to run.
	 */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
