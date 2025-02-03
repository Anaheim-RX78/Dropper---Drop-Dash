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
	 * @brief The elapsed time since the game started.
	 *
	 * This property stores the total elapsed time in seconds since the game started.
	 * It is used for tracking the duration of the game session.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float ElapsedTime = 0.0f;

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
	 * @brief The total number of coins collected by the player.
	 *
	 * This property stores the total number of coins that the player has collected
	 * throughout the game.
	 * It is used for score tracking and display purposes.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Score)
	int TotalCoins = 0;

	/**
	 * @brief The total number of Dragon Balls collected by the player.
	 *
	 * This property stores the total number of Dragon Balls that the player has collected
	 * throughout the game.
	 * It is used for tracking the player's progress in collecting Dragon Balls.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int DragonBallsCount = 0;

	/**
	 * @brief The identifier of the current level.
	 *
	 * This property stores the identifier of the current level that the
	 * player is playing. It is used for level management and loading.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Level)
	FString CurrentLevelIdentifier = "Level_01";

	/**
	 * @brief Indicates whether the game is over.
	 *
	 * This property stores a boolean value that indicates whether the game is over.
	 * It is used to track the game state and determine if the game has ended.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Game)
	bool IsGameOver = false;

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

	/**
	 * @brief Retrieves the player's current score.
	 *
	 * This function returns the player's current score, which is used
	 * to display the player's final score.
	 *
	 * @return The player's current score as an integer.
	 */
	UFUNCTION(BlueprintCallable)
	int GetScore() const;
};
