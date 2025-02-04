#pragma once

#include "CoreMinimal.h"
#include "Inventory.h"
#include "PlayerInteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "Dropper/DropperCharacter.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

/**
 * @brief Main character class for the game.
 *
 * This class represents the main character controlled by the player.
 * It includes properties and functions related to the character's movement, input actions, and camera setup.
 */
UCLASS()
class DROPPER_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/**
	 * @brief Sets default values for this character's properties.
	 *
	 * This constructor initializes the main character with default values.
	 * It sets up any necessary properties or configurations
	 * required for the character to function correctly when the game starts or when spawned.
	 */
	AMainCharacter();

protected:
	/**
	 * @brief Custom speed, default 100.
	 *
	 * This property defines the movement speed of the character.
	 * It can be adjusted to change how fast the character moves.
	 */
	UPROPERTY(EditAnywhere, Category=Movement)
	float Speed = 600.0f;

	/**
	 * @brief Camera component, needed to have a visualization attached to the character.
	 *
	 * This property holds a reference to the camera component attached to the character.
	 * It provides a view of the game world from the character's perspective.
	 */
	UPROPERTY(EditAnywhere, Category=Camera)
	UCameraComponent* Camera;

	/**
	 * @brief Arm used to have the right distance between the character and the camera.
	 *
	 * This property holds a reference to the spring arm component
	 * that positions the camera at a fixed distance from the character.
	 */
	UPROPERTY(EditAnywhere, Category=Camera)
	USpringArmComponent* SpringArm;

	/**
	 * @brief Interaction component for handling player interactions.
	 *
	 * This property holds a reference to the player interaction component
	 * attached to the character.
	 * It provides functionality to detect and
	 * handle interactions with interactable objects in the game world.
	 */
	UPROPERTY(EditAnywhere, Category=Interaction)
	UPlayerInteractionComponent* InteractionComponent;

	/**
	 * @brief Indicates whether the character is sprinting.
	 *
	 * This property is a boolean flag that indicates whether the character is currently sprinting.
	 * It is used to determine the character's movement speed and update the character's state accordingly.
	 */
	UPROPERTY(VisibleAnywhere)
	bool IsSprinting = false;

	/**
	 * @brief Called when the game starts or when spawned.
	 *
	 * This function is called when the game starts or when the character is spawned.
	 * It is used to initialize any properties
	 * or perform any setup required for the character to function correctly during gameplay.
	 */
	virtual void BeginPlay() override;

public:
	/**
	 * @brief Inventory component for managing the character's items.
	 *
	 * This property holds a reference to the inventory component attached to the character.
	 * It provides functionality to add, remove, and manage items within the character's inventory.
	 */
	UPROPERTY(EditAnywhere, Category=Inventory)
	UInventory* Inventory;

	/**
	 * @brief Gets the interaction component.
	 *
	 * This function returns a pointer to the player interaction component attached to the character.
	 * It provides access to the interaction component
	 * for handling interactions with interactable objects in the game world.
	 *
	 * @return A pointer to the player interaction component.
	 */
	UPlayerInteractionComponent* GetInteractionComponent() const { return InteractionComponent; }

	/**
	 * @brief Indicates whether the character was falling in the previous frame.
	 *
	 * This property is a boolean flag that indicates whether the character was falling in the previous frame.
	 * It can be used to detect transitions between falling and non-falling states.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Movement)
	bool CanDive = false;

	/**
	 * @brief Called every frame.
	 *
	 * This function is called once per frame and is used to update the character.
	 * It performs any necessary per-frame updates or logic required for the character to function correctly.
	 *
	 * @param DeltaTime The time elapsed since the last frame.
	 */
	virtual void Tick(float DeltaTime) override;

	/**
	 * @brief Called to bind functionality to input.
	 *
	 * This function is called to bind input actions to the character's functions.
	 * It sets up the input mappings for movement, looking, and other actions.
	 *
	 * @param PlayerInputComponent The input component to bind functionality to.
	 */
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/**
	 * @brief Called for movement input.
	 *
	 * This function is called to handle movement input from the player.
	 * It updates the character's position based on the input value.
	 *
	 * @param Value The input value for movement.
	 */
	void Move(const FVector2D& Value);

	/**
	 * @brief Called for looking input.
	 *
	 * This function is called to handle looking input from the player.
	 * It updates the character's view direction based on the input value.
	 *
	 * @param Value The input value for looking.
	 */
	void Look(const FVector2D& Value);

	/**
	 * @brief Called for sprinting input.
	 *
	 * This function is called to handle sprinting input from the player.
	 * It updates the character's speed based on the input value.
	 *
	 * @param Value The input value for sprinting.
	 */
	void Sprint(const FVector2D& Value);

	/**
	 * @brief Called for drop input.
	 *
	 * This function is called to handle drop input from the player.
	 * It updates the character's state based on the input value.
	 *
	 * @param Value The input value for dropping.
	 */
	void Drop(const FVector2D& Value);

	/**
	 * @brief Handles the scroll inventory action.
	 *
	 * This function is called when the scroll inventory input action is triggered.
	 * It processes the input value and performs the scroll inventory action for the main character.
	 *
	 * @param Value The input action value associated with the scroll inventory action.
	 */
	void ScrollInventory(const FVector2D& Value);
};
