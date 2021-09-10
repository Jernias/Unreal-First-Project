// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcherAnimInstance.h"

#include "MyArcher.h"
#include "GameFramework/PawnMovementComponent.h"

void UArcherAnimInstance::NativeInitializeAnimation()
{
	if(Pawn ==nullptr)
	{
		Pawn = TryGetPawnOwner();
		MyArcher = Cast<AMyArcher>(Pawn);
	}
}

void UArcherAnimInstance::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
		MyArcher = Cast<AMyArcher>(Pawn);
	}

	if(Pawn)
	{
		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
		MovementSpeed = LateralSpeed.Size();

		bIsInAir = Pawn->GetMovementComponent()->IsFalling();


	}
}

