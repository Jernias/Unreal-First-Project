// Fill out your copyright notice in the Description page of Project Settings.


#include "ColliderMovementComponent.h"

void UColliderMovementComponent:: TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!PawnOwner || !UpdatedComponent || ShouldSkipUpdate((DeltaTime)))
	{
		return;
	}

	FVector DesiredMovement = ConsumeInputVector().GetClampedToMaxSize(1.f)*MovementSpeed;

	if(!DesiredMovement.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovement, UpdatedComponent->GetComponentRotation(), true, Hit);

		if(Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(DesiredMovement, 1.f-Hit.Time, Hit.Normal, Hit);
			UE_LOG(LogTemp, Warning, TEXT("Hitting sth"));
		}
	}
}
