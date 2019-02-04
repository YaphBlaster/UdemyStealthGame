// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "FPSCharacter.h"
#include "FPSGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
	// Constant variables
	const float EXTRACTION_BOUNDARY = 200.0f;

	// Create a box component named OverlapComp
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));

	// Set the collision to true but to be viewed by queries only
	// Queries included ray-casts and overlaps
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	// Clear all collision responses by using ignore all (ECR_Ignore)
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);

	// Set collision response to 2 specific channels (pawn and overlap)
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// Set the boxes boundaries in the 3 axis'
	// FVector is just a simple vector
	OverlapComp->SetBoxExtent(FVector(EXTRACTION_BOUNDARY));

	// Set the RootCompent (Uppermost Parent) to OverlapComp
	RootComponent = OverlapComp;

	// By passing false to SetHiddenInGame this allows developers to view the bounding box of the component
	OverlapComp->SetHiddenInGame(false);

	// Overlap method
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleOverlap);

	// Create the DecalComp 
	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));

	// Set the size
	DecalComp->DecalSize = FVector(EXTRACTION_BOUNDARY);

	// Attach the component to the RootComponent as a child
	DecalComp->SetupAttachment(RootComponent);



}

void AFPSExtractionZone::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	// Cast the other actor to AFPSCharacter to see if the character is overlapping
	AFPSCharacter* MyPawn = Cast<AFPSCharacter>(OtherActor);

	// Check to see if MyPawn is null and player is carrying the objective
	if (MyPawn == nullptr) {
		return;
	}

	if (MyPawn->bIsCarryingObjective) {
		// Get the worlds GameMode (Get Auth is to get the servers GameMode)
		// Cast FPSGameMode class to game's GameMode
		AFPSGameMode* GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());

		// Check to see if GM exists
		// This function will always fail on clients because GameMode does not exist on client machines
		if (GM) {
			GM->CompleteMission(MyPawn, true);
		}

		// Double colon :: is for static functions
		UGameplayStatics::PlaySound2D(this, ObjectiveCompleteSound);
	}
	else {
		// Double colon :: is for static functions
		UGameplayStatics::PlaySound2D(this, ObjectiveMissingSound);
	}

	UE_LOG(LogTemp, Log, TEXT("Overlapped with extraction zone!"));


}




