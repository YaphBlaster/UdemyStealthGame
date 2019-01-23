// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGuardAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"

void AFPSGuardAIController::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), Waypoints);

	GoToRandomWaypoint();
}

// Whenever we override a function, you must call Super
void AFPSGuardAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AFPSGuardAIController::GoToRandomWaypoint, 3.0f, false);
}

ATargetPoint* AFPSGuardAIController::GetRandomWayPoint()
{
	auto index = FMath::RandRange(0, Waypoints.Num() - 1);
	return Cast<ATargetPoint>(Waypoints[index]);
}

void AFPSGuardAIController::GoToRandomWaypoint()
{
	MoveToActor(GetRandomWayPoint());
}
