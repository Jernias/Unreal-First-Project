// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingActor.h"


// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CustomStaticMesh"));

	initialLocation = FVector(0.f);

	InitialForce = FVector(1.f, 0.f, 0.f);

	force = FVector(1.f, 0.f, 0.f);
}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();

	PlacedLocation = GetActorLocation();


	StaticMesh->AddForce(force);

	//StaticMesh->AddTorqueInDegrees(force);
	
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bApplyForce)
	{
		FHitResult HitResult;
		AddActorLocalOffset(InitialForce, true, &HitResult);

		FVector HitLocation = HitResult.Location;

	}

}

