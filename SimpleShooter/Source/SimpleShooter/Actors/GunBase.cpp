// Copyright @CloudStudio 2020

#include "GunBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
//#include "DrawDebugHelpers.h"

AGunBase::AGunBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GunRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Gun Root"));
	SetRootComponent(GunRoot);

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	GunMesh->SetupAttachment(RootComponent);
}

void AGunBase::BeginPlay()
{
	Super::BeginPlay();	
}

void AGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGunBase::TriggerPulled() 
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GunMesh, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());

	if (!ensure(OwnerPawn)) return;

	FVector OUTLocation; 
	FRotator OUTRotation;
	
	OwnerPawn->GetController()->GetPlayerViewPoint(OUTLocation, OUTRotation);

	FVector TraceEnd = OUTLocation + OUTRotation.Vector() * ShootRange;
	FVector InShotDirection = -OUTRotation.Vector();
	FHitResult OUTHit;
	ECollisionChannel Bullet = ECC_GameTraceChannel1;// Custom trace channel 1

	if (!GetWorld()->LineTraceSingleByChannel(OUTHit, OUTLocation, TraceEnd, Bullet)) return;

	UGameplayStatics::
	SpawnEmitterAtLocation(GetWorld(), HitEffect, OUTHit.Location, InShotDirection.Rotation());

	if (!ensure(OUTHit.GetActor())) return;
	
	UGameplayStatics::
	ApplyDamage(OUTHit.GetActor(), ShootDamage, OwnerPawn->GetInstigatorController(), this, DamageType);

	// DrawDebugCamera(GetWorld(), OUTLocation, OUTRotation, 90.0f, 2.0f, FColor::Red, true);
	// DrawDebugLine(GetWorld(), OUTLocation, TraceEnd, FColor::Red, true);
	// DrawDebugPoint(GetWorld(), OUTHit.Location, 20.0f, FColor::Yellow, true);
}