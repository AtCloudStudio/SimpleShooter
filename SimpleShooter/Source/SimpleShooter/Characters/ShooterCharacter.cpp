// Copyright @CloudStudio 2020

#include "ShooterCharacter.h"
#include "SimpleShooter/Actors/ProjectileBase.h"
#include "SimpleShooter/Components/HealthComponent.h"
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

void AShooterCharacter::HandleDeath() 
{
	bIsDead = true;
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
}

void AShooterCharacter::CharacterDied()
{
	HandleDeath();
}

bool AShooterCharacter::IsCharacterDead() 
{
    return bIsDead;
}

void AShooterCharacter::Shoot() 
{
	if (!ensure(ProjectileClass)) return;

	AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(
		ProjectileClass, 
		ProjectileSpawnPoint->GetComponentLocation(), 
		ProjectileSpawnPoint->GetComponentRotation());

	TempProjectile->SetOwner(this);
}

void AShooterCharacter::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
}