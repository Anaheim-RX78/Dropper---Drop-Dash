#include "DropperGameInstance.h"

void UDropperGameInstance::OnLevelLoaded(const FString LevelIdentifier)
{
	// Check if the loaded level is the same as the current level.
	if (LevelIdentifier == this->CurrentLevelIdentifier)
	{
		this->CurrentLevelIdentifier = LevelIdentifier;
	}
	else
	{
		this->CurrentLevelIdentifier = "Level_01";
		this->Attempts = 0;
		this->TotalCoinsValue = 0;
	}
}

int UDropperGameInstance::GetScore() const
{
	return this->ElapsedTime / 60 + this->TotalCoins + this->TotalCoinsValue;
}
