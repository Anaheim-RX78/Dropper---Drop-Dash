#include "MainCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

class UEnhancedInputLocalPlayerSubsystem;

AMainCharacter::AMainCharacter()
{
	// Set this character to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	this->PrimaryActorTick.bCanEverTick = true;

	// Create a SpringArmComponent and attach it to the object
	this->SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	this->SpringArm->SetupAttachment(RootComponent);
	this->SpringArm->TargetArmLength = 500.0f;
	this->SpringArm->bUsePawnControlRotation = true;

	// Create a camera component and attach it to the spring arm.
	this->Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	this->Camera->SetupAttachment(this->SpringArm, USpringArmComponent::SocketName);
}

void AMainCharacter::BeginPlay()
{
	this->Super::BeginPlay();

	//Add Input Mapping Context
	const APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (IsValid(PlayerController))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AMainCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// Check, which is the forward direction
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// Get the forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// Get the right vector
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Add movement
		this->AddMovementInput(ForwardDirection, MovementVector.Y);
		this->AddMovementInput(RightDirection, MovementVector.X);
	}
	else
	{
		// Print a message to the screen if the controller is null.
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Controller is null");
	}
}

void AMainCharacter::Look(const FInputActionValue& Value)
{
	// Defensive coding: Print a message to the screen if the controller is null.
	if (GetController() == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Missing controller!");
		return;
	}

	// Get the FVector from the input action
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	// Add yaw and pitch input to controller
	this->AddControllerYawInput(LookAxisVector.X * -1);
	this->AddControllerPitchInput(LookAxisVector.Y);
}

void AMainCharacter::Tick(const float DeltaTime)
{
	this->Super::Tick(DeltaTime);
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	this->Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jump [Spacebar]
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AMainCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMainCharacter::StopJumping);

		// Move [W, A, S, D]
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::Move);

		// Look [Mouse position]
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component!"),
		       *GetNameSafe(this));
	}
}
