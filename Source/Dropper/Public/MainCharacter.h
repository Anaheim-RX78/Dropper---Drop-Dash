// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Dropper/DropperCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "MainCharacter.generated.h"

UCLASS()
class DROPPER_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	/**
	 * Mapper for every input action
	 */
	UPROPERTY(EditAnywhere, Category=Movement)
	UInputMappingContext* DefaultMappingContext;

	/**
	 * Custom speed, default 100
	 */
	UPROPERTY(EditAnywhere, Category=Movement)
	float Speed = 100.0f;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/**
	 * Camera component, needed to have a visualization attached to the character.
	 */
	UPROPERTY(EditAnywhere, Category=Camera)
	UCameraComponent* Camera;

	/**
	 * Arm used to have the right distance between the character and the camera.
	 */
	UPROPERTY(EditAnywhere, Category=Camera)
	USpringArmComponent* SpringArm;

	// TODO: Add inventory

	// TODO: Add player interaction component

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
