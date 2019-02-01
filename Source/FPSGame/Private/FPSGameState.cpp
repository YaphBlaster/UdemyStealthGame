// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameState.h"

// When creating replicated function implementations, you must append "_Implementation" to the end of the function's name
// Visual Assist X does this automatically when you select the "Create Implementation" button in the header file

void AFPSGameState::MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bMissionSuccess)
{
	// Iterate over every pawn in the world
	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; It++)
	{
		// Get current pawn
		APawn* Pawn = It->Get();
		// If the pawn exists and it is locally controlled, then
		if (Pawn && Pawn->IsLocallyControlled())
		{
			// Disable current pawn's input
			// Expects a player controller but you can provide nullptr and it will default to the player controller the pawn has
			Pawn->DisableInput(nullptr);
		}
	}
}
