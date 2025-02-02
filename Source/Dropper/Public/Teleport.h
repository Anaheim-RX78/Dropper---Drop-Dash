#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "Teleport.generated.h"

UCLASS()
class DROPPER_API ATeleport : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FVector SpawnPoint;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	USoundCue* TeleportSound = nullptr;

public:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// Sets default values for this actor's properties
	ATeleport();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PlayTeleportSound() const;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
