#pragma once

#include "CoreMinimal.h"
#include "InteractableComponent.h"
#include "ItemActor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

class USoundCue;
class UCapsuleComponent;

/**
 * @brief Represents a coin actor in the game.
 *
 * The ACoin class defines the properties and behavior of a coin actor in the game world.
 * It includes components for visual representation, collision detection, and sound effects.
 * The class also handles the coin's animation and interaction with other actors.
 */
UCLASS()
class DROPPER_API ACoin : public AItemActor
{
	GENERATED_BODY()

public:
	/**
	 * @brief Constructor for the ACoin class.
	 *
	 * This function sets the default values for the properties of the ACoin actor.
	 * It initializes the coin's components and properties to ensure it behaves correctly
	 * when spawned in the game world.
	 *
	 * @return ACoin object with default property values set.
	 */
	ACoin();

protected:
	/**
	 * @brief Initializes the coin actor when the game starts or when it is spawned.
	 *
	 * This function is called automatically by the Unreal Engine when the game begins or when the coin actor is spawned into the game world.
	 * It is used to set up any necessary initial state or properties for the coin actor.
	 *
	 * @return Void This function does not return a value.
	 */
	virtual void BeginPlay() override;

	/**
	 * @brief Represents the score value of a single coin.
	 *
	 * This property defines the number of points a player receives when collecting this coin.
	 * It can be edited in the Unreal Editor, allowing for easy customization of the coin's worth.
	 *
	 * @note The default value is set to 1, but can be adjusted as needed for different coin types or gameplay balance.
	 */
	UPROPERTY(EditAnywhere)
	int CoinValue = 1;

	/**
	 * @brief The static mesh component representing the visual appearance of the coin.
	 *
	 * This property defines the 3D model used to render the coin in the game world.
	 * It can be edited in the Unreal Editor, allowing for easy customization of the coin's appearance.
	 *
	 * @note The mesh should typically be a coin-shaped 3D model for visual consistency.
	 */
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	/**
	 * @brief The interactable component for the coin.
	 *
	 * This property holds a reference to the UInteractableComponent, which allows the coin to be interacted with.
	 * It can be used to trigger interaction events and handle interaction logic for the coin.
	 *
	 * @note This property is visible in the Unreal Editor but cannot be edited.
	 */
	UPROPERTY(VisibleAnywhere)
	UInteractableComponent* InteractableComponent;

	/**
	 * @brief Called when an actor begins to overlap with this coin.
	 *
	 * This function is triggered when another actor starts overlapping with the coin's collision component.
	 * It can be used to implement coin collection logic, such as increasing the player's score or playing a sound effect.
	 *
	 * @param OverlappedComponent The primitive component that was overlapped.
	 * @param OtherActor The actor that overlapped this component.
	 * @param OtherComp The primitive component that overlapped this component.
	 * @param OtherBodyIndex The body index of the component doing the overlapping.
	 * @param bFromSweep True if the overlap was triggered by a sweep test.
	 * @param SweepResult The hit result from the sweep that triggered this overlap.
	 *
	 * @return Void This function does not return a value.
	*/
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp,
	                            int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/**
	 * @brief Sets the animation speed for the coin's movement.
	 *
	 * This property determines how fast the coin's animation plays. It can be adjusted
	 * to speed up or slow down the animation, allowing for dynamic visual effects.
	 *
	 * @note The default value is set to 1, representing the normal speed of the animation.
	 *       Increasing the value will speed up the animation, while decreasing it will slow it down.
	 *
	 * @return The current animation speed as a float.
	 */
	UPROPERTY(EditAnywhere)
	float AnimationSpeed = 1;

	/**
	 * @brief Initial position used for the animation starting point.
	 *
	 * This property represents the initial position of the coin actor when the animation starts.
	 * It is used to determine the starting point for any movement or animation applied to the coin.
	 * The value is set when the coin is spawned and remains constant throughout the animation.
	 *
	 * @note This property is visible in the Unreal Editor but cannot be edited.
	 */
	UPROPERTY(VisibleAnywhere)
	FVector InitialPosition;

	/**
	 * @brief Delta movement used for animation length.
	 *
	 * This property represents the change in position of the coin actor over the course of the animation.
	 * It defines how far the coin will move from its initial position to its target position.
	 * The value can be edited in the Unreal Editor to customize the movement distance for different coins.
	 *
	 * @note The default value is set to a zero vector, meaning no movement.
	 */
	UPROPERTY(EditAnywhere)
	FVector DeltaMovement = FVector(0, 0, 50);

	/**
	 * @brief Final position for the animation.
	 *
	 * This property represents the target position of the coin actor at the end of the animation.
	 * It is calculated based on the initial position and the delta movement.
	 * The value is set automatically during the animation process and is visible in the Unreal Editor.
	 *
	 * @note This property is visible in the Unreal Editor but cannot be edited.
	 */
	UPROPERTY(VisibleAnywhere)
	FVector TargetPosition;

	/**
	 * @brief Time elapsed since the first rendered frame.
	 *
	 * This property is used for animation purposes to track the amount of time that has passed
	 * since the coin actor was first rendered. It is updated every frame to ensure accurate
	 * animation timing.
	 *
	 * @note This property is visible in the Unreal Editor but cannot be edited.
	 */
	UPROPERTY(VisibleAnywhere)
	float Time = 0;

	/**
	 * @brief Sound effect played when the coin is collected.
	 *
	 * This property holds a reference to a USoundCue object that represents the sound effect
	 * to be played when the coin is collected by the player. It can be edited in the Unreal Editor,
	 * allowing for easy customization of the sound effect for different coins.
	 *
	 * @note The sound effect should be a short audio clip that provides feedback to the player upon coin collection.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundCue* SoundEffect;

public:
	/**
	 * @brief Called every frame to update the coin actor.
	 *
	 * This function is called automatically by the Unreal Engine every frame.
	 * It is used to update the coin actor's state, including its position, animation, and other properties.
	 *
	 * @param DeltaTime The time in seconds it took to render the last frame.
	 *                  This value is used to ensure smooth and consistent animation and movement.
	 */
	virtual void Tick(float DeltaTime) override;
};
