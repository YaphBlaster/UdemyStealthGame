// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSLaunchPad.h"
#include "Components/BoxComponent.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSLaunchPad::AFPSLaunchPad()
{
	// Create Static Mesh component named "MeshComp"
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	// Remove all collisions
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// Set MeshComp as the RootComponent (uppermost parent)
	RootComponent = MeshComp;

	// Create Static Mesh component named "ArrowComp"
	ArrowComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowComp"));
	// Attach the ArrowComp to the MeshComp (which is the root)
	ArrowComp->SetupAttachment(MeshComp);

	// Create a Box Component named "BoxComp" (this will be used for collision detection)
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	// Set the collision to query only (raycasts, sweeps, overlaps)
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// Clear all collision response channels
	BoxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	//Set response channel for Pawn (for player) to overlap the launchpad
	BoxComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	//Set response channel for PhysicsBody (physics objects) to overlap the launchpad
	BoxComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	// Attach this component to the MeshComp (which is the root)
	BoxComp->SetupAttachment(MeshComp);

}

// Called when the game starts or when spawned
void AFPSLaunchPad::BeginPlay()
{
	Super::BeginPlay();

}

// Implementation from the .header file
// Simple method to play the given ParticleSystem
void AFPSLaunchPad::PlayEffects()
{
	// Play the PartcleSystem (LaunchFX) at the actor's location
	UGameplayStatics::SpawnEmitterAtLocation(this, LaunchFX, GetActorLocation());
}

// Implementation from the .header file
// We will override the stock NotifyActorBeginOverlap function with our own
void AFPSLaunchPad::NotifyActorBeginOverlap(AActor* OtherActor)
{
	// Force strength constant
	// This is the amount of strength that will be used to push the Pawn or PhysicsBody
	const int FORCE_STRENGTH = 1000.0f;

	// Cast the overlapped actor (OtherActor) to the FPSCharacter class
	AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(OtherActor);

	// Cast the overlapped actor's RootComponent (Root StaticMesh of OtherActor) to StaticMeshComponent class
	UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(OtherActor->GetRootComponent());

	// If the OtherActor was the Pawn
	if (MyCharacter) {
		// Launch the character into the air
		MyCharacter->LaunchCharacter((this->GetActorForwardVector()*FORCE_STRENGTH) + FVector(0.0f, 0.0f, FORCE_STRENGTH), true, true);
		// Play particle effect
		PlayEffects();
	}
	// Else if OtherActor was a PhysicsBody
	else if (MeshComponent) {
		// Add an impulse to the MeshComponent
		MeshComponent->AddImpulse((this->GetActorForwardVector()*FORCE_STRENGTH) + FVector(0.0f, 0.0f, FORCE_STRENGTH), NAME_None, true);
		// Play particle effect
		PlayEffects();
	}

	// Show actor name to the output log
	UE_LOG(LogTemp, Warning, TEXT("Other Actor = %s"), *OtherActor->GetName());
}

