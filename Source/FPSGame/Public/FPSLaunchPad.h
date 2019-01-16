// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSLaunchPad.generated.h"

class UBoxComponent;

UCLASS()
class FPSGAME_API AFPSLaunchPad : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFPSLaunchPad();

protected:
	//Pointer Instantiation

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* ArrowComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UBoxComponent* BoxComp;

	// Exposed to blueprints
	// Particle System that will be played when the LaunchPad is activated
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		UParticleSystem* LaunchFX;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Method called when effect is to be played
	void PlayEffects();

public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;


};
