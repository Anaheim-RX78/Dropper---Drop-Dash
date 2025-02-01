#pragma once

#include "CoreMinimal.h"
#include "InteractableComponent.h"
#include "Components/SceneComponent.h"
#include "PlayerInteractionComponent.generated.h"


/**
 * @brief Component that handles player interactions in the game.
 *
 * This component can be attached to any actor to enable player interaction
 * functionality. It provides properties to define the interaction distance,
 * the collision channel used for interaction, and the current interactable
 * component being interacted with.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPPER_API UPlayerInteractionComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	/**
	 * @brief Default constructor for UPlayerInteractionComponent.
	 *
	 * This constructor sets default values for this component's properties.
	 */
	UPlayerInteractionComponent();

protected:
	/**
	 * @brief The maximum distance at which interactions can occur.
	 *
	 * This property defines the maximum distance from the player at which
	 * interactions can be detected and handled.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Interaction)
	float InteractionDistance = 1000.0f;

	/**
	 * @brief The collision channel used for interaction detection.
	 *
	 * This property defines the collision channel that will be used to
	 * detect interactable objects in the game world.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Interaction)
	TEnumAsByte<ECollisionChannel> InteractionChannel;

	/**
	 * @brief The current interactable component being interacted with.
	 *
	 * This property holds a reference to the interactable component that
	 * the player is currently interacting with, if any.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	UInteractableComponent* CurrentInteractable = nullptr;

	/**
	 * @brief Called when the game starts.
	 *
	 * This method is called when the game starts or when the component is spawned.
	 * It is used to initialize any properties or states that the component needs
	 * to function properly.
	 */
	virtual void BeginPlay() override;

	/**
	 * @brief Checks the interaction range.
	 *
	 * This method checks if there are any interactable components within the interaction
	 * range of the player. If an interactable component is found within the range, it
	 * updates the CurrentInteractable property with the reference to that component.
	 */
	void CheckInteractionRange();

public:
	/**
	 * @brief Called every frame.
	 *
	 * This method is called every frame and is used to update the component.
	 * It can be used to perform any per-frame logic or updates that the component needs.
	 *
	 * @param DeltaTime The time elapsed since the last frame.
	 * @param TickType The type of tick this is.
	 * @param ThisTickFunction The tick function that is being executed.
	 */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * @brief Initiates an interaction.
	 *
	 * This method is called to perform an interaction with the current interactable component.
	 * It triggers the interaction logic defined in the interactable component.
	 */
	void Interact() const;
};
