#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputMap.generated.h"

class UInputAction;
class UInputMappingContext;

/**
 * @brief Data asset that maps input actions to their corresponding contexts.
 *
 * This class is used to define and store input mappings for the game. It allows
 * the association of input actions with specific input contexts, enabling the
 * game to handle different input configurations and mappings.
 */
UCLASS()
class DROPPER_API UInputMap : public UDataAsset
{
	GENERATED_BODY()

public:
	/**
		 * @brief The input mapping context.
		 *
		 * This property holds a reference to the input mapping context that defines
		 * the input configuration for the game. It is used to map input actions to
		 * their corresponding input contexts.
		 */
	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* Context;

	/**
		 * @brief The input actions mapped to their corresponding names.
		 *
		 * This property holds a map of input action names to their corresponding
		 * UInputAction objects. It is used to define and store the input actions
		 * that can be triggered in the game.
		 */
	UPROPERTY(EditAnywhere, Category = Input)
	TMap<FString, UInputAction*> Actions;
};
