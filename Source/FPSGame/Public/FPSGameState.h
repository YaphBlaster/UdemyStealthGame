// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FPSGameState.generated.h"

/**
 * GameState can be used as a GameMode that can have replicated functions and properties
 * This allows us to send calls to clients, which GameMode cannot do
 */
UCLASS()
class FPSGAME_API AFPSGameState : public AGameStateBase
{
	GENERATED_BODY()


public:
	// Net MultiCast
	// NetMulticast means that if this function is called on the server, it will get sent to all the clients (including the server)
	UFUNCTION(NetMulticast, Reliable)
		void MulticastOnMissionComplete(APawn* InstigatorPawn, bool bMissionSuccess);
};
