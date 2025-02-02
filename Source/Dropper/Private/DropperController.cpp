#include "DropperController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void ADropperController::Tick(const float DeltaSeconds)
{
	this->Super::Tick(DeltaSeconds);
}

void ADropperController::SetupInputComponent()
{
	this->Super::SetupInputComponent();

	// Bind input actions to their corresponding handler functions
	const ULocalPlayer* LocalPlayer = GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	Subsystem->ClearAllMappings();

	if (!this->InputMap)
	{
		// The input map is null, display a message to the screen.
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Missing the input map!");
		return;
	}

	// Add the input map context
	Subsystem->AddMappingContext(this->InputMap->Context, 0);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(this->InputMap->Actions["Jump"], ETriggerEvent::Started, this,
	                                   &ADropperController::Jump);
	EnhancedInputComponent->BindAction(this->InputMap->Actions["Move"], ETriggerEvent::Triggered, this,
	                                   &ADropperController::Move);
	EnhancedInputComponent->BindAction(this->InputMap->Actions["Look"], ETriggerEvent::Triggered, this,
	                                   &ADropperController::Look);
	EnhancedInputComponent->BindAction(this->InputMap->Actions["Interact"], ETriggerEvent::Started, this,
	                                   &ADropperController::OnInteract);
	EnhancedInputComponent->BindAction(this->InputMap->Actions["Sprint"], ETriggerEvent::Started, this,
	                                   &ADropperController::Sprint);
}

void ADropperController::OnPossess(APawn* InPawn)
{
	this->Super::OnPossess(InPawn);
	if (AMainCharacter* PossessedPawn = Cast<AMainCharacter>(InPawn)) { this->MainCharacter = PossessedPawn; }
}

void ADropperController::Jump(const FInputActionValue& Value)
{
	this->MainCharacter->Jump();
}

void ADropperController::Sprint(const FInputActionValue& Value)
{
	this->MainCharacter->Sprint(Value.Get<FVector2D>());
}

void ADropperController::Move(const FInputActionValue& Value)
{
	this->MainCharacter->Move(Value.Get<FVector2D>());
}

void ADropperController::Look(const FInputActionValue& Value)
{
	this->MainCharacter->Look(Value.Get<FVector2D>());
}

void ADropperController::OnInteract(const FInputActionValue& Value)
{
	this->MainCharacter->GetInteractionComponent()->Interact();
}
