#include "Coin.h"

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
	this->Mesh->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnBeginOverlap);

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

void ACoin::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                           int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the other actor is a MainCharacter (player) and if it has a valid pointer.
	const AMainCharacter* Character = Cast<AMainCharacter>(OtherActor);
	if (IsValid(Character))
	{
		// Play sound effect if provided.
		if (SoundEffect)
		{
			UGameplayStatics::PlaySound2D(this, SoundEffect, 1.0f, 1.0f, 0.28f);
		}
		// TODO: Add save in inventory
		this->Destroy();
	}
}

void ACoin::Tick(const float DeltaTime)
{
	this->Super::Tick(DeltaTime);

	// Configure the floating animation
	this->Time += DeltaTime * AnimationSpeed;
	const float t = 0.5f - 0.5f * FMath::Cos(Time);

	this->SetActorLocation(FMath::Lerp(InitialPosition, TargetPosition, t));
}
