#include "DropperGameInstance.h"

void UDropperGameInstance::OnLevelLoaded(FString LevelIdentifier)
{
	// Check if the loaded level is the same as the current level.
	if (LevelIdentifier == this->CurrentLevelIdentifier)
	{
		this->CurrentLevelIdentifier = "Level_01";
		// TODO: Reset only some things
	}
	else
	{
		this->CurrentLevelIdentifier = "Level_01";
		// TODO: Reset everything
	}
}
