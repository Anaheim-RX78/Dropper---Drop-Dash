#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"

/**
 * @brief Struct representing the payload for an interaction event.
 *
 * This struct contains information about the interaction event, including
 * the actor that initiated the interaction, and the location where the
 * interaction took place.
 */
USTRUCT(BlueprintType)
struct FInteractionPayload
{
	GENERATED_BODY()

	/**
	 * @brief The actor that initiated the interaction.
	 */
	UPROPERTY(BlueprintReadOnly)
	AActor* Interactor;

	/**
	 * @brief The location where the interaction took place.
	 */
	UPROPERTY(BlueprintReadOnly)
	FVector Location;
};

/**
 * @brief Delegate for handling interaction events.
 *
 * This delegate is used to broadcast interaction events with a payload
 * containing information about the interaction.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractionHandler, FInteractionPayload, Payload);

/**
 * @brief Component that handles interactions in the game.
 *
 * This component can be attached to any actor to enable interaction
 * functionality. It provides methods to get the interaction name and
 * to handle interaction events.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DROPPER_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/**
	 * @brief Default constructor for UInteractableComponent.
	 *
	 * This constructor sets default values for this component's properties.
	 */
	UInteractableComponent();

protected:
	/**
	 * @brief The name of the interaction.
	 *
	 * This property holds the name of the interaction and can be edited in the editor.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FString InteractionName;

	/**
	 * @brief Called when the game starts.
	 *
	 * This method is called when the game starts or when the component is spawned.
	 * It is used to initialize any properties or states that the component needs
	 * to function properly.
	 */
	virtual void BeginPlay() override;

public:
	/**
	 * @brief Delegate for handling interaction events.
	 *
	 * This property is used to assign and broadcast interaction events
	 * with a payload containing information about the interaction.
	 */
	UPROPERTY(BlueprintAssignable)
	FInteractionHandler OnInteract;

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
	 * @brief Handles the interaction event.
	 *
	 * This method is called to handle the interaction event with the provided payload.
	 * It can be called from both C++ and Blueprints.
	 *
	 * @param Payload The payload containing information about the interaction event.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void Interact(FInteractionPayload Payload);

	/**
	 * @brief Retrieves the name of the interaction.
	 *
	 * This method returns the name of the interaction as a string.
	 * It can be called from both C++ and Blueprints.
	 *
	 * @return The name of the interaction.
	 */
	UFUNCTION(BlueprintCallable)
	FString GetInteractionName() const;
};
