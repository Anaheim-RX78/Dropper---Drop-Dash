#include "Teleport.h"

#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATeleport::ATeleport()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	this->PrimaryActorTick.bCanEverTick = true;
	this->BoxComponent = CreateDefaultSubobject<UBoxComponent>("Teleport");
	this->BoxComponent->SetRelativeScale3D(FVector(45, 55, 1.5));
	this->BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATeleport::OnBeginOverlap);

	this->SetRootComponent(this->BoxComponent);
}

// Called when the game starts or when spawned
void ATeleport::BeginPlay()
{
	Super::BeginPlay();
}

void ATeleport::PlayTeleportSound() const
{
	if (this->TeleportSound)
	{
		UGameplayStatics::PlaySound2D(this, this->TeleportSound);
	}
}

// Called every frame
void ATeleport::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATeleport::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                               const FHitResult& SweepResult)
{
	AMainCharacter* Character = Cast<AMainCharacter>(OtherActor);
	if (IsValid(Character))
	{
		// Teleport the character to the spawn point.
		Character->SetActorLocation(this->SpawnPoint);
		// Play sound effect if provided.
		this->PlayTeleportSound();
	}
}
