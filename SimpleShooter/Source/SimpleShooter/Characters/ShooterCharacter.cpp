// Copyright @CloudStudio 2020

#include "ShooterCharacter.h"
#include "SimpleShooter/Actors/GunBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AShooterCharacter::AShooterCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Third Person Camera"));
    ThirdPersonCamera->SetupAttachment(SpringArm);
}

void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Hide original weapon skeletal mesh
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	// Spawn custom weapon, attach it to Mesh component, and set its owner to the character
	Gun = GetWorld()->SpawnActor<AGunBase>(Weapon);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
}

void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("Move Forward"), this, &ThisClass::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Move Right"), this, &ThisClass::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Look Up"), this, &ThisClass::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Look Right"), this, &ThisClass::LookRight);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &ThisClass::Shoot);
}

void AShooterCharacter::MoveForward(float AxisValue) 
{
	AddMovementInput(GetActorForwardVector() * AxisValue * MoveSpeed * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::MoveRight(float AxisValue) 
{
	AddMovementInput(GetActorRightVector() * AxisValue * MoveSpeed * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookUp(float AxisValue) 
{
	AddControllerPitchInput(AxisValue * RotateSpeed * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRight(float AxisValue) 
{
	AddControllerYawInput(AxisValue * RotateSpeed * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::Shoot() 
{
	if (!ensure(Gun)) return;

	Gun->TriggerPulled();
}