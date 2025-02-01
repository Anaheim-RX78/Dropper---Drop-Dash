#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemData.generated.h"

class AItemActor;
/**
 * @brief Data asset class representing item data.
 *
 * This class represents a data asset that holds information about an item.
 * It contains properties such as the item's name, description, and the class of the item actor.
 * This data asset can be used to define different types of items in the game.
 */
UCLASS()
class DROPPER_API UItemData : public UDataAsset
{
	GENERATED_BODY()

public:
	/**
	 * @brief The name of the item.
	 *
	 * This property holds the name of the item. It is used to identify the item in the game.
	 */
	UPROPERTY(EditAnywhere, Category=Item)
	FString Name;

	/**
	 * @brief The description of the item.
	 *
	 * This property holds the description of the item. It provides additional information about the item.
	 */
	UPROPERTY(EditAnywhere, Category=Item)
	FString Description;

	/**
	 * @brief The class of the item actor.
	 *
	 * This property holds a reference to the class of the item actor that represents this item in the game world.
	 * It is used to spawn the item actor when needed.
	 */
	UPROPERTY(EditAnywhere, Category=Item)
	TSubclassOf<AItemActor> Item;
};
