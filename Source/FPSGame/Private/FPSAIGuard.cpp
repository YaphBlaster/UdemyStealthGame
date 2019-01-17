// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));


	// Binding to Events
	// In order to see the required parameters, Alt+G on the function (OnSeePawn)
	// Then Alt+G again to on the Delegate (FSeePawnDelegate)
	// When you find the parameter type(s), you can create the pointer in the .header file
	// Implement from the .header file and add the function as second parameter (as seen below)
	// Second parameter is in this order: [&CLASS_NAME::FUNCTION_NAME]
	PawnSensingComp->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	PawnSensingComp->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();

}

void AFPSAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	if (SeenPawn == nullptr)
	{
		return;
	}

	// NOTE: Inside of Editor, Press F1 to see wireframe to more easily see debug spheres
	// This will run every half a second because the sensing interval in the AIPawn is set to 0.5
	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 10.0f);
}

void AFPSAIGuard::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{

	// NOTE: Inside of Editor, Press F1 to see wireframe to more easily see debug spheres
	// This will run every half a second because the sensing interval in the AIPawn is set to 0.5
	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Green, false, 10.0f);
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


