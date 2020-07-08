// Copyright @CloudStudio 2020

#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "particles/ParticleSystemComponent.h"

AProjectileBase::AProjectileBase()
{
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->SetNotifyRigidBodyCollision(true);
	SetRootComponent(ProjectileMesh);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = MovementSpeed;
	ProjectileMovement->MaxSpeed = MovementSpeed;

	ProjectileTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Projectile Trail"));
	ProjectileTrail->SetupAttachment(RootComponent);
	ProjectileTrail->bAutoActivate = false;

	InitialLifeSpan = 1.0f;
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	if (!ProjectileMesh) return;

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		FVector NormalImpulse,
		const FHitResult& Hit) 
{
	if (!ProjectileTrail) return;

	ProjectileTrail->Activate();

	AActor* TempOwner = GetOwner();

	if (!ensure(TempOwner)) return;

	if (OtherActor && OtherActor != this && OtherActor != TempOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, TempOwner->GetInstigatorController(), this, DamageType);
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation(), FRotator::ZeroRotator);
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	}
	
	Destroy();
}