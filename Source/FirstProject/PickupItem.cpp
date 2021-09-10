// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItem.h"

#include "MyArcher.h"

APickupItem::APickupItem()
{
	
}

void APickupItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if(OtherActor)
	{
		AMyArcher* Archer = Cast<AMyArcher>(OtherActor);
		if(Archer)
		{
			Destroy();
		}
	}

}

void APickupItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}


