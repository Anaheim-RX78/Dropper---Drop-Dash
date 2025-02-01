#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DropperGameInstance.generated.h"

/**
 * @brief Game instance class for the Dropper game.
 *
 * This class extends the UGameInstance class and is used to manage game-wide
 * states and functionalities, such as score tracking and level management.
 */
UCLASS()
class DROPPER_API UDropperGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	/**
	 * @brief The maximum depth reached in the game.
	 *
	 * This property stores the maximum depth that the player has reached
	 * in the game. It is used for score tracking and display purposes.
	 */
	UPROPERTY(EditAnywhere, Category = Score)
	float MaxDepth = 0;

	/**
	 * @brief The number of attempts made by the player.
	 *
	 * This property stores the number of attempts the player has made
	 * in the game. It is used for tracking player progress and performance.
	 */
	UPROPERTY(EditAnywhere, Category = Score)
	int Attempts = 0;

	/**
	 * @brief The identifier of the current level.
	 *
	 * This property stores the identifier of the current level that the
	 * player is playing. It is used for level management and loading.
	 */
	UPROPERTY(EditAnywhere, Category = Level)
	FString CurrentLevelIdentifier = "Level_01";

	/**
	 * @brief Called when a level is loaded.
	 *
	 * This function is called when a level is loaded in the game. It updates
	 * the current level identifier to the specified level identifier.
	 *
	 * @param LevelIdentifier The identifier of the loaded level.
	 */
	UFUNCTION(BlueprintCallable)
	void OnLevelLoaded(FString LevelIdentifier);
};
