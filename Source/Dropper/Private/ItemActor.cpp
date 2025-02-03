#include "ItemActor.h"

AItemActor::AItemActor(): Data(nullptr)
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	this->PrimaryActorTick.bCanEverTick = true;
}

void AItemActor::BeginPlay()
{
	this->Super::BeginPlay();
}

void AItemActor::Tick(const float DeltaTime)
{
	this->Super::Tick(DeltaTime);
}

void AItemActor::UseItem()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Unsupported function, override it!");
}
