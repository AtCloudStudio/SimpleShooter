// Copyright @CloudStudio 2020

#include "ShooterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AShooterCharacter::AShooterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Third Person Camera"));
    ThirdPersonCamera->SetupAttachment(SpringArm);
}

void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
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
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
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