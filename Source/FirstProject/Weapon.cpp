// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

AWeapon::AWeapon()
{

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(GetRootComponent());

}

void AWeapon::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (OtherActor)
	{
		AMyArcher* Archer = Cast<AMyArcher>(OtherActor);
		if (Archer)
		{
			Archer->SetActiveOVerlappingItem(this);
		}
	}
}

void AWeapon::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	if (OtherActor)
	{
		AMyArcher* Archer = Cast<AMyArcher>(OtherActor);
		if (Archer)
		{
			Archer->SetActiveOVerlappingItem(nullptr);
		}
	}
}

void AWeapon::Equip(AMyArcher* Char)
{
	if(Char)
	{
		SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
		SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

		SkeletalMesh->SetSimulatePhysics(false);

		const USkeletalMeshSocket* WeaponSocket = Char->GetMesh()->GetSocketByName("MeleeSocket");

		if(WeaponSocket)
		{
			WeaponSocket->AttachActor(this, Char->GetMesh());
			bRotate = false;

			if (Char->GetEquippedWeapon()) 
			{
				Char->GetEquippedWeapon()->Destroy();
			}
			Char->SetEquippedWeapon(this);
			Char->SetActiveOVerlappingItem(nullptr);
		}
		if(OnEquipSound)
		{
			UGameplayStatics::PlaySound2D(this, OnEquipSound);
		}
	}

}


