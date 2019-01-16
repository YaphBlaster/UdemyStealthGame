// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}


void AFPSGameMode::CompleteMission(APawn* InstigatorPawn)
{
	if (InstigatorPawn) {
		// Disable input
		// Expects a player controller but you can provide nullptr and it will default to the player controller the pawn has
		InstigatorPawn->DisableInput(nullptr);

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

				// Check to see if the player controller exists
				if (PC) {

					// Set the player controllers view target to the new position
					PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SpectatingViewpointClass is nullptr. Please update GameMode class with valid subclass. Cannot change spectating view target"))
		}
	}

	OnMissionCompleted(InstigatorPawn);


}
