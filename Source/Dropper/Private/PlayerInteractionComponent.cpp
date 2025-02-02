#include "PlayerInteractionComponent.h"

UPlayerInteractionComponent::UPlayerInteractionComponent(): InteractionChannel()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame. You can turn these features
	// off to improve performance if you don't need them.
	this->PrimaryComponentTick.bCanEverTick = true;
}


void UPlayerInteractionComponent::BeginPlay()
{
	this->Super::BeginPlay();
}

void UPlayerInteractionComponent::CheckInteractionRange()
{
	// Perform a line trace to detect interactable objects within the interaction range.
	FHitResult InteractableFound;

	const FVector ComponentLocation = this->GetComponentLocation();
	this->GetWorld()->LineTraceSingleByChannel(
		InteractableFound, // The result of the line trace
		ComponentLocation, // The start location of the line trace
		ComponentLocation + this->GetForwardVector() * this->InteractionDistance, // The end location of the line trace
		this->InteractionChannel // The collision channel to use for the line trace
	);

	const AActor* InteractableActor = InteractableFound.GetActor();

	// Check if no actor was hit by the line trace
	if (InteractableActor == nullptr)
	{
		// No actor was hit by the line trace, set CurrentInteractable to nullptr.
		this->CurrentInteractable = nullptr;
		return;
	}

	UInteractableComponent* Component = InteractableActor->GetComponentByClass<UInteractableComponent>();

	if (this->CurrentInteractable == nullptr && Component)
	{
		// No current interactable actor, but a new one was found.
		this->CurrentInteractable = Component;
	}
	else if (this->CurrentInteractable && Component && Component != this->CurrentInteractable)
	{
		// An existing interactable actor was found, but it's different from the current one.
		CurrentInteractable = Component;
	}
}

void UPlayerInteractionComponent::TickComponent(const float DeltaTime, const ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	this->Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	this->CheckInteractionRange();
}

void UPlayerInteractionComponent::Interact() const
{
	// Check if the current interactable actor is still valid.
	if (this->CurrentInteractable == nullptr) { return; }

	// Call the Interact method of the current interactable actor with a payload containing the owning actor.
	this->CurrentInteractable->Interact(FInteractionPayload{GetOwner()});
}
