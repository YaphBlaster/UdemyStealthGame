// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameState.h"
#include "FPSPlayerController.h"

// When creating replicated function implementations, you must append "_Implementation" to the end of the function's name
// Visual Assist X does this automatically when you select the "Create Implementation" button in the header file

void AFPSGameState::MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bMissionSuccess)
{

	// Iterate over every player controller in the world
	// The syntax is a little strange but it's basically a regular loop (for i=0; i<array.length(); i++)
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	{
		AFPSPlayerController* PC = Cast<AFPSPlayerController>(It->Get());

		// Check if PC is valid and is the local player controller, then
		if (PC && PC->IsLocalController())
		{
			PC->OnMissionCompleted(InstigatorPawn, bMissionSuccess);

			// Derive the client's pawn from the client's player controller
			APawn* MyPawn = PC->GetPawn();

			// If valid
			if (MyPawn)
			{
				// Disable current pawn's input
				// Expects a player controller but you can provide nullptr and it will default to the player controller the pawn has
				// In this case we now the exact player controller of this pawn so we pass it through
				MyPawn->DisableInput(PC);
			}
		}
	}
}
