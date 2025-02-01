#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Dropper/DropperCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
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
	 * @brief Mapper for every input action.
	 *
	 * This property holds a reference to the input mapping context that maps input actions to the character's movements.
	 */
	UPROPERTY(EditAnywhere, Category=Movement)
	UInputMappingContext* DefaultMappingContext;

	/**
	 * @brief Custom speed, default 100.
	 *
	 * This property defines the movement speed of the character.
	 * It can be adjusted to change how fast the character moves.
	 */
	UPROPERTY(EditAnywhere, Category=Movement)
	float Speed = 100.0f;

	/**
	 * @brief Jump Input Action.
	 *
	 * This property holds a reference to the input action used for jumping.
	 * It allows the character to perform a jump when the action is triggered.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/**
	 * @brief Move Input Action.
	 *
	 * This property holds a reference to the input action used for moving the character.
	 * It allows the character to move based on player input.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/**
	 * @brief Look Input Action.
	 *
	 * This property holds a reference to the input action used for looking around.
	 * It allows the character to change its view direction based on player input.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

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

	// TODO: Add inventory

	// TODO: Add player interaction component

	/**
	 * @brief Called when the game starts or when spawned.
	 *
	 * This function is called when the game starts or when the character is spawned.
	 * It is used to initialize any properties
	 * or perform any setup required for the character to function correctly during gameplay.
	 */
	virtual void BeginPlay() override;

	/**
	 * @brief Called for movement input.
	 *
	 * This function is called to handle movement input from the player.
	 * It updates the character's position based on the input value.
	 *
	 * @param Value The input value for movement.
	 */
	void Move(const FInputActionValue& Value);

	/**
	 * @brief Called for looking input.
	 *
	 * This function is called to handle looking input from the player.
	 * It updates the character's view direction based on the input value.
	 *
	 * @param Value The input value for looking.
	 */
	void Look(const FInputActionValue& Value);

public:
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
};
