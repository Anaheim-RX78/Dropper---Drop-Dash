#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "GameFramework/Actor.h"
#include "ItemActor.generated.h"

/**
 * @brief Actor class representing an item in the game world.
 *
 * This class represents an item actor that can be spawned in the game world. It contains properties
 * and functions related to the item, such as its data and behavior when the game starts or every frame.
 */
UCLASS()
class DROPPER_API AItemActor : public AActor
{
	GENERATED_BODY()

public:
	/**
	 * @brief Sets default values for this actor's properties.
	 *
	 * This constructor initializes the item actor with default values. It sets up any necessary properties
	 * or configurations required for the item actor to function correctly when the game starts or when spawned.
	 */
	AItemActor();

	/**
	 * @brief Reference to the item data associated with this actor.
	 *
	 * This property holds a reference to the `UItemData` object that represents the type of item
	 * this actor represents. It is used to identify the item type and access its properties,
	 * such as name, description, and other relevant data.
	 */
	UPROPERTY(EditAnywhere, Category=Item)
	UItemData* Data;

protected:
	/**
	 * @brief Called when the game starts or when spawned.
	 *
	 * This function is called when the game starts or when the actor is spawned.
	 * It is used to initialize any properties or perform any setup required for the item actor
	 * to function correctly during gameplay.
	 */
	virtual void BeginPlay() override;

public:
	/**
	 * @brief Called every frame.
	 *
	 * This function is called once per frame and is used to update the item actor.
	 * It performs any necessary per-frame updates or logic required for the item actor to function correctly.
	 *
	 * @param DeltaTime The time elapsed since the last frame.
	 */
	virtual void Tick(float DeltaTime) override;
};
