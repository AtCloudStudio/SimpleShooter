// Copyright @CloudStudio 2020

#include "GunBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleShooter/Actors/ProjectileBase.h"
#include "SimpleShooter/Characters/PlayerShooter.h"
#include "DrawDebugHelpers.h"

AGunBase::AGunBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GunRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Gun Root"));
	SetRootComponent(GunRoot);

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	GunMesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(GunMesh);
}

void AGunBase::BeginPlay()
{
	Super::BeginPlay();	

	Player = Cast<APlayerShooter>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGunBase::TriggerPulled() 
{
	LaunchProjectile();
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GunMesh, TEXT("MuzzleFlashSocket"));
	// DrawShootRay();
}

void AGunBase::LaunchProjectile() 
{
	if (!ensure(ProjectileClass)) return;

	AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(
		ProjectileClass, 
		ProjectileSpawnPoint->GetComponentLocation(), 
		ProjectileSpawnPoint->GetComponentRotation());

	TempProjectile->SetOwner(Player);
}

void AGunBase::DrawShootRay()
{
	FVector LaunchLocation = ProjectileSpawnPoint->GetComponentLocation(); 
	FRotator LaunchRotation = ProjectileSpawnPoint->GetComponentRotation();

	FVector TraceEnd = LaunchLocation + LaunchRotation.Vector() * ShootRange;
	FHitResult OUTHit;
	ECollisionChannel Bullet = ECC_GameTraceChannel1;

	if (!GetWorld()->LineTraceSingleByChannel(OUTHit, LaunchLocation, TraceEnd, Bullet)) return;

	DrawDebugLine(GetWorld(), LaunchLocation, TraceEnd, FColor::Red, true);
	DrawDebugPoint(GetWorld(), OUTHit.Location, 10.0f, FColor::Red, true);
}

// Ray trace from camera, directly apply damage by gun, no projectile spawn
void AGunBase::CourseOriginalShootImplementation() 
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());

	if (!ensure(OwnerPawn)) return;

	FVector OUTLocation; 
	FRotator OUTRotation;
	
	OwnerPawn->GetController()->GetPlayerViewPoint(OUTLocation, OUTRotation);

	FVector TraceEnd = OUTLocation + OUTRotation.Vector() * ShootRange;
	FVector InShotDirection = -OUTRotation.Vector();
	FHitResult OUTHit;
	ECollisionChannel Bullet = ECC_GameTraceChannel1;// Custom trace channel 1
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	if (!GetWorld()->LineTraceSingleByChannel(OUTHit, OUTLocation, TraceEnd, Bullet, Params)) return;

	if (!ensure(HitEffect)) return;
	
	UGameplayStatics::
	SpawnEmitterAtLocation(GetWorld(), HitEffect, OUTHit.Location, InShotDirection.Rotation());

	if (!ensure(OUTHit.GetActor())) return;
	
	UGameplayStatics::
	ApplyDamage(OUTHit.GetActor(), ShootDamage, OwnerPawn->GetInstigatorController(), this, DamageType);

	DrawDebugCamera(GetWorld(), OUTLocation, OUTRotation, 90.0f, 2.0f, FColor::Red, true);
	DrawDebugLine(GetWorld(), OUTLocation, TraceEnd, FColor::Red, true);
	DrawDebugPoint(GetWorld(), OUTHit.Location, 10.0f, FColor::Red, true);
}