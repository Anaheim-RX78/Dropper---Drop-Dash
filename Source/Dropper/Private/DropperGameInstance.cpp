#include "DropperGameInstance.h"

#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"

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

		// Clear the inventory
		ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		const AMainCharacter* MainCharacter = Cast<AMainCharacter>(Character);
		if (IsValid(MainCharacter))
		{
			MainCharacter->Inventory->ClearInventory();
		}
		else
		{
			// The character is not an instance of MainCharacter, display an error message
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("No main character found!"));
		}
	}
}

int UDropperGameInstance::GetScore() const
{
	return this->ElapsedTime / 60 + this->TotalCoins + this->TotalCoinsValue;
}
