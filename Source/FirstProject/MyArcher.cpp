// Fill out your copyright notice in the Description page of Project Settings.


#include "MyArcher.h"

#include <string>

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Math/Color.h"
#include "DrawDebugHelpers.h"
#include "Weapon.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyArcher::AMyArcher()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;		//Rotate cameraboom based on controller

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;	//only cameraboom rotates with controller

	BaseTurnRate = 65.f;
	BaseLookUpRate = 65.f;

	SprintSpeed = 1.f;

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 600.f, 0.f );
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = .2f;

	bPickUp = false;
}

// Called when the game starts or when spawned
void AMyArcher::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyArcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if(Sprinting)	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

// Called to bind functionality to input
void AMyArcher::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction(TEXT("Pickup"), IE_Pressed, this, &AMyArcher::PickUp);

	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &AMyArcher::StartSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &AMyArcher::StopSprint);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMyArcher::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMyArcher::MoveRight);


	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("TurnRate"), this, &AMyArcher::TurnAtRate);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AMyArcher::LookUpAtRate);
	
}

void AMyArcher::MoveForward(float Value)
{
	if( Controller != nullptr && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), GetActorLocation()+ Direction * 500.f, 100,FColor::Red);

		Value = Value* SprintSpeed;

		//UE_LOG(LogTemp, Warning, TEXT("walking"));
		AddMovementInput(Direction, Value);
	}
}

void AMyArcher::MoveRight(float Value)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	Value *= SprintSpeed;
	AddMovementInput(Direction, Value);
}

void AMyArcher::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMyArcher::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMyArcher::StartSprint()
{
	Sprinting = true;
	SprintSpeed = 1000.f;

	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	UE_LOG(LogTemp, Warning, TEXT("Sprint start"));
}

void AMyArcher::StopSprint()
{
	Sprinting = false;
	SprintSpeed = 700.f;
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AMyArcher::PickUp()
{
	bPickUp = true;

	if(ActiveOverlappingItem)
	{
		AWeapon* Weapon = Cast<AWeapon>(ActiveOverlappingItem);
		if(Weapon)
		{
			Weapon->Equip(this);
			SetActiveOVerlappingItem(nullptr);
		}
	}
}








