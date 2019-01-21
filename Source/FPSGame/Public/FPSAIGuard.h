// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;

// Enum declaration
// NOTES:
// Always outside of main class
// Convention is to start with 'E' (EAIState)
// BlueprintType is used to expose the enum to blueprints
// uint8 is needed to expose to blueprint as well (otherwise it could have been left blank)
UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle,

	Suspiscious,

	Alerted
};

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPawnSensingComponent* PawnSensingComp;

	// Method derived from FSeePawnDelegate
	// Needs UFUNCTION() or else code will not know how to bind event
	UFUNCTION()
		void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
		void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	FRotator OriginalRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NewRotation")
		FRotator NewRotation;

	UFUNCTION()
		void ResetOrientation();

	FTimerHandle TimerHandle_ResetOrientation;

	EAIState GuardState;

	void SetGuardState(EAIState NewState);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
		void OnStateChanged(EAIState NewState);


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
