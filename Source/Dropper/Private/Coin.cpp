#include "Coin.h"

#include "DropperGameInstance.h"
#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ACoin::ACoin()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	this->PrimaryActorTick.bCanEverTick = true;

	// Attach a mesh to the object
	this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	this->Mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Overlap);
	this->Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	this->Mesh->SetRelativeLocation(FVector(0, 0, 50));

	// Set the mesh as the root component
	this->SetRootComponent(this->Mesh);
}

void ACoin::BeginPlay()
{
	this->Super::BeginPlay();

	// Set up the initial position, and the target position for animation purposes.
	this->InitialPosition = GetActorLocation();
	this->TargetPosition = GetActorLocation() + DeltaMovement;
}

void ACoin::GetCoin(const FInteractionPayload Payload)
{
	// Check if the interactor is a valid MainCharacter.
	const AMainCharacter* Character = Cast<AMainCharacter>(Payload.Interactor);
	if (IsValid(Character))
	{
		// Play sound effect if provided.
		if (this->SoundEffect)
		{
			UGameplayStatics::PlaySound2D(this, this->SoundEffect, 1.0f, 1.0f, 0.28f);
		}
		// Add the coin to the character's inventory and destroy the coin.
		Character->Inventory->AddItem(this, 1);

		const FSlot* InventorySlot = Character->Inventory->GetSlotByData(this->Data);

		// Update the total values of the coins
		UDropperGameInstance* DropperInstance =
			Cast<UDropperGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (IsValid(DropperInstance))
		{
			DropperInstance->TotalCoinsValue += this->CoinValue;

			// Print the total coins value
			FString Message = FString::Printf(TEXT("Total value: %d"), DropperInstance->TotalCoinsValue);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Message);

			// Print the coin value
			Message = FString::Printf(TEXT("Total value for the new coin: %d"), this->CoinValue);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Message);
		}

		const FString Message = FString::Printf(TEXT("You have now %d coins in total"), InventorySlot->Amount);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Message);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "New coin obtained!");
	}
}

void ACoin::Tick(const float DeltaTime)
{
	this->Super::Tick(DeltaTime);

	// Configure the floating animation
	this->Time += DeltaTime * this->AnimationSpeed;
	const float t = 0.5f - 0.5f * FMath::Cos(this->Time);

	this->SetActorLocation(FMath::Lerp(this->InitialPosition, this->TargetPosition, t));
}
