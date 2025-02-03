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
	 * @brief The number of attempts made by the player.
	 *
	 * This property stores the number of attempts the player has made
	 * in the game. It is used for tracking player progress and performance.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Score)
	int Attempts = 0;

	/**
	 * @brief The total value of coins collected by the player.
	 *
	 * This property stores the total value of coins that the player has collected
	 * throughout the game.
	 * It is used for score tracking and display purposes.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Score)
	int TotalCoinsValue = 0;

	/**
	 * @brief The identifier of the current level.
	 *
	 * This property stores the identifier of the current level that the
	 * player is playing. It is used for level management and loading.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Level)
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
