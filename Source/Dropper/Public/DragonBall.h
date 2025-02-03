#pragma once

#include "CoreMinimal.h"
#include "ItemActor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "DragonBall.generated.h"


/**
 * @brief Dragon Ball actor
 *
 * This class represents the DragonBall actor in the game.
 */
UCLASS()
class DROPPER_API ADragonBall : public AItemActor
{
	GENERATED_BODY()

	/**
	 * @brief Main mesh
	 *
	 * The static mesh component for the DragonBall.
	 * This component represents the visual appearance of the DragonBall in the game.
	 * It is editable anywhere in the editor.
	 */
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	/**
	 * @brief Sound effect played when the DragonBall is collected.
	 *
	 * This property holds a reference to a USoundCue object that represents the sound effect
	 * to be played when the DragonBall is collected by the player. It can be edited in the Unreal Editor,
	 * allowing for easy customization of the sound effect for different DragonBalls.
	 *
	 * @note The sound effect should be a short audio clip that provides feedback to the player upon collection.
	 */
	UPROPERTY(EditAnywhere)
	USoundCue* CollectionSound;

public:
	/**
	 * @brief Constructor for the ADragonBall class.
	 *
	 * This function sets the default values for the properties of the ADragonBall actor.
	 * It initializes the DragonBall's components and properties to ensure it behaves correctly
	 * when spawned in the game world.
	 *
	 * @return ADragonBall object with default property values set.
	 */
	ADragonBall();

protected:
	/**
	 * @brief Initializes the DragonBall actor when the game starts or when it is spawned.
	 *
	 * This function is called automatically by the Unreal Engine when the game begins or when the DragonBall actor is spawned into the game world.
	 * It is used to set up any necessary initial state or properties for the DragonBall actor.
	 *
	 * @return Void This function does not return a value.
	 */
	virtual void BeginPlay() override;

	/**
     * @brief Handles the overlap event when another actor begins to overlap with the DragonBall.
     *
     * This function is called automatically by the Unreal Engine when another actor begins to overlap
     * with the DragonBall actor. It is used to handle the interaction between the DragonBall and other actors,
     * such as adding the DragonBall to the player's inventory and destroying the DragonBall actor.
     *
     * @param OverlappedComponent The component that was overlapped.
     * @param OtherActor The other actor that caused the overlap event.
     * @param OtherComp The component of the other actor that was involved in the overlap.
     * @param OtherBodyIndex The index of the other body.
     * @param bFromSweep Whether the overlap was caused by a sweep.
     * @param SweepResult The result of the sweep, if applicable.
     *
     * @return Void This function does not return a value.
     */
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	/**
	 * @brief Called every frame to update the DragonBall actor.
	 *
	 * This function is called automatically by the Unreal Engine every frame.
	 * It is used to update the DragonBall actor's state, including its position, animation, and other properties.
	 *
	 * @param DeltaTime The time in seconds it took to render the last frame.
	 *                  This value is used to ensure smooth and consistent animation and movement.
	 */
	virtual void Tick(float DeltaTime) override;
};
