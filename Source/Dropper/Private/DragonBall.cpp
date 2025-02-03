#include "DragonBall.h"

#include "DropperGameInstance.h"
#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"

ADragonBall::ADragonBall()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the mesh
	this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	this->Mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Overlap);
	this->Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	this->Mesh->OnComponentBeginOverlap.AddDynamic(this, &ADragonBall::OnBeginOverlap);

	// Set up the mesh as the object root component
	SetRootComponent(this->Mesh);
}

void ADragonBall::BeginPlay()
{
	this->Super::BeginPlay();
}

void ADragonBall::Tick(const float DeltaTime)
{
	this->Super::Tick(DeltaTime);
}

void ADragonBall::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult& SweepResult)
{
	const AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
	if (IsValid(MainCharacter))
	{
		UDropperGameInstance* DropperInstance = Cast<UDropperGameInstance>(
			UGameplayStatics::GetGameInstance(GetWorld()));
		if (IsValid(DropperInstance))
		{
			DropperInstance->DragonBallsCount++;
		}
		// Add the item into the inventory
		MainCharacter->Inventory->AddItem(this->Data, 1);

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "Congratulations! You got a dragon ball!");

		// Remove the item from the scene
		this->Destroy();

		// Play a sound if present
		if (this->CollectionSound)
		{
			UGameplayStatics::PlaySound2D(this, this->CollectionSound);
		}
	}
}
