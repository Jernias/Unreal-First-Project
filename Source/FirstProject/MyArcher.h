// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyArcher.generated.h"

UCLASS()
class FIRSTPROJECT_API AMyArcher : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyArcher();

	/** Cameraboom positions camera behind the player  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, Category = Player)
	float SprintSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	void StartSprint();
	void StopSprint();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Items")
	bool bPickUp;
	void PickUp();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	bool Sprinting;


	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items")
	class AWeapon* EquippedWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Items")
	class AItem* ActiveOverlappingItem;

	FORCEINLINE void SetEquippedWeapon(AWeapon* Weapon) { EquippedWeapon = Weapon; }
	FORCEINLINE AWeapon* GetEquippedWeapon() { return EquippedWeapon; }
	FORCEINLINE void SetActiveOVerlappingItem(AItem* Item) { ActiveOverlappingItem = Item; }
};
