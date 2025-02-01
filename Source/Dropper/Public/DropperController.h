#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "InputMap.h"
#include "MainCharacter.h"
#include "GameFramework/PlayerController.h"
#include "DropperController.generated.h"

/**
 * @brief Controller class for the Dropper game.
 *
 * This class extends APlayerController and is responsible for handling player input,
 * managing the main character, and processing interaction events in the game.
 */
UCLASS()
class DROPPER_API ADropperController : public APlayerController
{
	GENERATED_BODY()

protected:
	/**
	 * @brief Reference to the main character.
	 *
	 * This property holds a reference to the main character controlled by this controller.
	 * It is used to access and manage the main character's properties and actions.
	 */
	UPROPERTY(VisibleAnywhere)
	AMainCharacter* MainCharacter;

	/**
	 * @brief The input map for the controller.
	 *
	 * This property holds a reference to the input map that defines the input
	 * actions and their corresponding contexts for the controller. It is used
	 * to manage and configure the input mappings for the player.
	 */
	UPROPERTY(EditAnywhere, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMap* InputMap;

	/**
	 * @brief The distance at which the player can interact with interactable objects.
	 *
	 * This property holds the distance at which the player can interact with interactable objects.
	 * It is used to determine when to trigger interaction events and provide feedback to the player.
	 */
	UPROPERTY(VisibleAnywhere)
	float Distance;

	/**
	 * @brief Called every frame.
	 *
	 * This method is called every frame and is used to update the controller.
	 * It can be used to perform any per-frame logic or updates that the controller needs.
	 *
	 * @param DeltaSeconds The time elapsed since the last frame.
	 */
	virtual void Tick(float DeltaSeconds) override;

	/**
	 * @brief Sets up the input component for the controller.
	 *
	 * This method is called to bind input actions to their corresponding handler functions.
	 * It is used to configure the input mappings and ensure that the controller can
	 * respond to player input.
	 */
	virtual void SetupInputComponent() override;

	/**
	 * @brief Called when the controller possesses a pawn.
	 *
	 * This method is called when the controller takes control of a pawn. It is used to
	 * initialize any properties or states that the controller needs to manage the pawn.
	 *
	 * @param InPawn The pawn that the controller is taking control of.
	 */
	virtual void OnPossess(APawn* InPawn) override;

	/**
	 * @brief Handles the jump action.
	 *
	 * This method is called when the jump input action is triggered. It processes
	 * the input value and performs the jump action for the main character.
	 *
	 * @param Value The input action value associated with the jump action.
	 */
	UFUNCTION()
	void Jump(const FInputActionValue& Value);

	/**
	 * @brief Handles the move action.
	 *
	 * This method is called when the move input action is triggered. It processes
	 * the input value and performs the movement action for the main character.
	 *
	 * @param Value The input action value associated with the move action.
	 */
	UFUNCTION()
	void Move(const FInputActionValue& Value);

	/**
	 * @brief Handles the look action.
	 *
	 * This method is called when the look input action is triggered. It processes
	 * the input value and performs the look action for the main character.
	 */
	UFUNCTION()
	void Look(const FInputActionValue& Value);

	/**
	 * @brief Handles the interact action.
	 *
	 * This method is called when the interact input action is triggered. It processes
	 * the input value and performs the interaction action for the main character.
	 */
	UFUNCTION()
	void OnInteract(const FInputActionValue& Value);
};
