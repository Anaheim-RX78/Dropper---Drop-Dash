// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"

#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
ACoin::ACoin()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	this->Mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Overlap);
	this->Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	this->Mesh->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnBeginOverlap);

	SetRootComponent(this->Mesh);
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();

	InitialPosition = GetActorLocation();
	TargetPosition = GetActorLocation() + DeltaMovement;
}

void ACoin::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                           int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainCharacter* Character = Cast<AMainCharacter>(OtherActor);
	if (IsValid(Character))
	{
		if (SoundEffect)
		{
			UGameplayStatics::PlaySound2D(this, SoundEffect, 1.0f, 1.0f, 0.28f);
		}
		// TODO: Add save in inventory
		this->Destroy();
	}
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Time += DeltaTime * Speed;
	const float t = 0.5f - 0.5f * FMath::Cos(Time);

	SetActorLocation(FMath::Lerp(InitialPosition, TargetPosition, t));
}
