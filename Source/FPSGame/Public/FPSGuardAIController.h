// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Array.h"
#include "FPSGuardAIController.generated.h"

class ATargetPoint;
class AActor;

/**
 *
 */
UCLASS()
class FPSGAME_API AFPSGuardAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Manual override of BeginPlay
	void BeginPlay() override;

	// Manual override of OnMoveCompleted found in AIController [Line: 228]
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

protected:
	UPROPERTY()
		TArray<AActor*> Waypoints;

	UFUNCTION()
		ATargetPoint* GetRandomWayPoint();

	UFUNCTION()
		void GoToRandomWaypoint();

public:
	FTimerHandle TimerHandle;

};
