// Copyright @CloudStudio 2020

#include "PlayerShooter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

APlayerShooter::APlayerShooter() 
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Third Person Camera"));
    ThirdPersonCamera->SetupAttachment(SpringArm);
}

void APlayerShooter::BeginPlay() 
{
    Super::BeginPlay();
}

void APlayerShooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Move Forward"), this, &ThisClass::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Move Right"), this, &ThisClass::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Look Up"), this, &ThisClass::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Look Right"), this, &ThisClass::LookRight);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &ThisClass::Shoot);
}

void APlayerShooter::MoveForward(float AxisValue) 
{
	AddMovementInput(GetActorForwardVector() * AxisValue * MoveSpeed * GetWorld()->GetDeltaSeconds());
}

void APlayerShooter::MoveRight(float AxisValue) 
{
	AddMovementInput(GetActorRightVector() * AxisValue * MoveSpeed * GetWorld()->GetDeltaSeconds());
}

void APlayerShooter::LookUp(float AxisValue) 
{
	AddControllerPitchInput(AxisValue * RotateSpeed * GetWorld()->GetDeltaSeconds());
}

void APlayerShooter::LookRight(float AxisValue) 
{
	AddControllerYawInput(AxisValue * RotateSpeed * GetWorld()->GetDeltaSeconds());
}

void APlayerShooter::HandleDeath() 
{
    Super::HandleDeath();

	// TODO Added player death effect
}