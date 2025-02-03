#include "MainCharacter.h"

#include "DropperGameInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

class UEnhancedInputLocalPlayerSubsystem;

AMainCharacter::AMainCharacter()
{
	this->PrimaryActorTick.bCanEverTick = true;
	this->SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring arm");
	this->SpringArm->SetupAttachment(this->GetRootComponent());
	this->SpringArm->TargetArmLength = 500.0f;
	this->SpringArm->bUsePawnControlRotation = true;

	this->Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	this->Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	this->Inventory = CreateDefaultSubobject<UInventory>("Inventory");

	this->InteractionComponent = CreateDefaultSubobject<UPlayerInteractionComponent>("Interaction Component");
	this->InteractionComponent->SetupAttachment(this->Camera);
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	this->GetCharacterMovement()->MaxWalkSpeed = Speed;
	UGameInstance* Instance = UGameplayStatics::GetGameInstance(GetWorld());
	const UDropperGameInstance* DropperInstance = Cast<UDropperGameInstance>(Instance);

	if (!IsValid(DropperInstance))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
		                                 "Configure it in project settings -> Project -> Maps & Modes -> Game Instance");
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red,
		                                 "The game instance is not an instance of DropperGameInstance");
	}
}

void AMainCharacter::Tick(const float DeltaTime)
{
	this->Super::Tick(DeltaTime);
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	this->Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMainCharacter::Move(const FVector2D& Value)
{
	this->AddMovementInput(FRotationMatrix(FRotator(0, GetControlRotation().Yaw, 0)).GetUnitAxis(EAxis::Y), Value.X);
	this->AddMovementInput(FRotationMatrix(FRotator(0, GetControlRotation().Yaw, 0)).GetUnitAxis(EAxis::X), Value.Y);
}

void AMainCharacter::Look(const FVector2D& Value)
{
	this->AddControllerPitchInput(Value.Y);
	this->AddControllerYawInput(Value.X);
}

void AMainCharacter::Sprint(const FVector2D& Value)
{
	this->IsSprinting = !this->IsSprinting;
	if (this->IsSprinting)
	{
		this->GetCharacterMovement()->MaxWalkSpeed = Speed * 2;
	}
	else
	{
		this->GetCharacterMovement()->MaxWalkSpeed = Speed;
	}
}
