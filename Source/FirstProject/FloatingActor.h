// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingActor.generated.h"

UCLASS()
class FIRSTPROJECT_API AFloatingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingActor();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ActorMeshes")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "FloatingActorVariables")
	FVector initialLocation;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category="FloatingActorVariables")
	FVector PlacedLocation;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "FloatingActorVariables")
	FVector WorldOrigin;

	UPROPERTY(EditDefaultsOnly , BlueprintReadWrite, Category = "FloatingActorVariables")
	bool bInitializeFloatingActorLocation;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "FloatingActorVariables")
	bool bApplyForce;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "FloatingActorVariables")
	FVector InitialForce;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "FloatingActorVariables")
	FVector force;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
