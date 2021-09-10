// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveItem.h"

#include "MyArcher.h"

AExplosiveItem::AExplosiveItem()
{
	
}

void AExplosiveItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (OtherActor)
	{
		AMyArcher* Archer = Cast<AMyArcher>(OtherActor);
		if (Archer)
		{
			Destroy();
		}
	}
}

void AExplosiveItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

}

