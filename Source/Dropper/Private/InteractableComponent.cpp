#include "InteractableComponent.h"

UInteractableComponent::UInteractableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame. You can turn these features
	// off to improve performance if you don't need them.
	this->PrimaryComponentTick.bCanEverTick = true;
}

void UInteractableComponent::BeginPlay()
{
	this->Super::BeginPlay();
}

void UInteractableComponent::TickComponent(const float DeltaTime, const ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	this->Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInteractableComponent::Interact(const FInteractionPayload Payload)
{
	// Broadcast the interaction event to any listeners
	this->OnInteract.Broadcast(Payload);
}

FString UInteractableComponent::GetInteractionName() const
{
	// Retrieve the interaction name
	return this->InteractionName;
}
