// Copyright @CloudStudio 2020

#include "ShooterCharacter.h"
#include "SimpleShooter/Actors/ProjectileBase.h"
#include "SimpleShooter/Components/HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"

AShooterCharacter::AShooterCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// Hide original weapon skeletal mesh
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	GunMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(GunMesh);
	
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	bIsDead = false;
}

void AShooterCharacter::Shoot() 
{
	if (!ensure(MuzzleFlash || GunMesh || ProjectileClass || ProjectileSpawnPoint)) return;

	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GunMesh, TEXT("MuzzleFlashSocket"));
	// GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(LaunchShake, 1.0f);

	AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(
		ProjectileClass, 
		ProjectileSpawnPoint->GetComponentLocation(), 
		ProjectileSpawnPoint->GetComponentRotation());

	TempProjectile->SetOwner(this);
}

void AShooterCharacter::HandleDeath() 
{
	bIsDead = true;
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AShooterCharacter::CharacterDied()
{
	HandleDeath();
}

bool AShooterCharacter::IsCharacterDead() 
{
    return bIsDead;
}

void AShooterCharacter::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
}