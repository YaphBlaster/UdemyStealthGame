// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSPlayerController.generated.h"

/**
 * Player controllers exist on both the server and the client that owns this player controller (Pawns exist everywhere)
 */
UCLASS()
class FPSGAME_API AFPSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, Category = "PlayerController")
		void OnMissionCompleted(APawn* InstigatorPawn, bool bMissionSuccess);

};
