// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "FPSGameState.h"

// GameModes only run on servers
// There are no instances of GameMode on clients
AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();

	// Set the GameMode's GameState class to our FPSGameState's class
	// StaticClass returns the reference's static class
	// This line makes it so that when we call GetGameState, it will return this reference
	GameStateClass = AFPSGameState::StaticClass();
}


void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, bool bMissionSuccess)
{
	if (InstigatorPawn) {

		// Check to see if there is a SpectatingViewPointClass set up
		if (SpectatingViewpointClass)
		{

			TArray<AActor*> ReturnedActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActors);

			// If the ReturnedActors array returned with any elements
			// Change ViewTarget if any valid actor found
			if (ReturnedActors.Num() > 0) {

				// Set the NewViewTarget to the first element in the ReturnedActors array
				AActor* NewViewTarget = ReturnedActors[0];

				// Get the pawns controller and cast it to PlayerController
				APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());

				// Iterate over every player controller in the world
				// The syntax is a little strange but it's basically a regular loop (for i=0; i<array.length(); i++)
				for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
				{
					APlayerController* PC = It->Get();
					if (PC) {
						// Set the player controllers view target to the new position
						// SetViewTargetWithBlend is always replicated
						PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
					}
				}

			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SpectatingViewpointClass is nullptr. Please update GameMode class with valid subclass. Cannot change spectating view target"))
		}
	}

	// Create GameState reference
	AFPSGameState* GS = GetGameState<AFPSGameState>();

	// If the GameState exists (Cast was successful)
	if (GS)
	{
		// When referncing replicated functions, do not use the `${FUNCTION_NAME}_Implementation` method
		// Instead use the regularly named function
		GS->MulticastOnMissionComplete(InstigatorPawn, bMissionSuccess);
	}

	OnMissionCompleted(InstigatorPawn, bMissionSuccess);

}
