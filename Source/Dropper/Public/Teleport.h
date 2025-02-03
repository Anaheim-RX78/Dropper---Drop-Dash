#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "Teleport.generated.h"

/**
 * @brief Actor class representing a teleportation point in the game world.
 *
 * This class represents a teleport actor that can be placed in the game world.
 * It contains properties and functions related to the teleportation behavior,
 * such as the spawn point, collision detection, and sound effects for teleportation and winning.
 */
UCLASS()
class DROPPER_API ATeleport : public AActor
{
	GENERATED_BODY()

	/**
	 * @brief The spawn point location for teleportation.
	 *
	 * This property specifies the location to which the character will be teleported
	 * when they overlap with this teleport actor.
	 * It is an editable property that can be set
	 * in the editor to define the exact coordinates of the spawn point.
	 */
	UPROPERTY(EditAnywhere, Category=Spawn)
	FVector SpawnPoint;

	/**
	 * @brief The box component used for collision detection.
	 *
	 * This property holds a reference to the `UBoxComponent` that defines the collision box for the teleport actor.
	 * It is used to detect overlaps with other actors, triggering the teleportation event when an overlap occurs.
	 * The box component is visible in the editor and can be adjusted to fit the desired collision area.
	 */
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;

	/**
	 * @brief The sound cue to play when teleportation occurs.
	 *
	 * This property holds a reference to the `USoundCue` object that represents the sound effect
	 * to be played when the teleportation event occurs.
	 * It is an editable property
	 * that can be set in the editor to specify the desired sound cue for the teleportation effect.
	 */
	UPROPERTY(EditAnywhere)
	USoundCue* TeleportSound = nullptr;

public:
	/**
	 * @brief Handles the event when another actor begins to overlap with this actor.
	 *
	 * This function is called when another actor begins to overlap with this actor's box component.
	 * It checks if the overlapping actor is a valid `AMainCharacter` and, if so, plays the teleport sound
	 * and teleports the character to the specified spawn point.
	 *
	 * @param OverlappedComponent The component that was overlapped.
	 * @param OtherActor The actor that caused the overlap event.
	 * @param OtherComp The specific component of the other actor that was involved in the overlap.
	 * @param OtherBodyIndex The index of the other body.
	 * @param bFromSweep Whether the overlap was caused by a sweep.
	 * @param SweepResult The result of the sweep, if applicable.
	 */
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/**
	 * @brief Sets default values for this actor's properties.
	 *
	 * This constructor initializes the teleport actor with default values.
	 * It sets up any necessary properties or configurations
	 * required for the teleport actor to function correctly when the game starts or when spawned.
	 */
	ATeleport();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString NewLevelName;

protected:
	/**
	 * @brief Called when the game starts or when spawned.
	 *
	 * This function is called when the game starts or when the actor is spawned.
	 * It is used to initialize any properties or perform any setup required for the teleport actor
	 * to function correctly during gameplay.
	 */
	virtual void BeginPlay() override;

	/**
	 * @brief Plays the teleport sound effect.
	 *
	 * This function plays the teleport sound effect if a sound cue is provided.
	 * It is used to provide audio feedback when the teleportation event occurs.
	 */
	void PlayTeleportSound() const;

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
