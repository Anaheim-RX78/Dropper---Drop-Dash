// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coin.generated.h"

class USoundCue;
class UCapsuleComponent;

UCLASS()
class DROPPER_API ACoin : public AActor
{
	GENERATED_BODY()

public:
	/**
	 * Sets default values for this actor's properties
	 */
	ACoin();

protected:
	/**
	 * Called when the game starts or when spawned
	 */
	virtual void BeginPlay() override;

	/**
	 * Score for the single coin
	 */
	UPROPERTY(EditAnywhere)
	int Value = 1;

	/**
	 * Actor mesh
	 */
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	/**
	 * Capsule component used for collision
	 */
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* Capsule;

	/**
	 * Function called every time an actor overlaps the coin
	 */
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp,
	                            int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/**
	 * Animation speed
	 */
	UPROPERTY(EditAnywhere)
	float Speed = 1;

	/**
	 * Initial position used for the animation starting point
	 */
	UPROPERTY(VisibleAnywhere)
	FVector InitialPosition;

	/**
	 * Delta movement used for animation length
	 */
	UPROPERTY(EditAnywhere)
	FVector DeltaMovement;

	/**
	 * Final position for the animation
	 */
	UPROPERTY(VisibleAnywhere)
	FVector TargetPosition;

	/**
	 * Time elapsed since the first rendered frame
	 */
	UPROPERTY(VisibleAnywhere)
	float Time = 0;

	/**
     * Sound effect played when the coin is collected
     */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundCue* SoundEffect;

public:
	/**
	 * Called every frame
	 * @param DeltaTime How much time in seconds it takes to render a single frame
	 */
	virtual void Tick(float DeltaTime) override;
};
