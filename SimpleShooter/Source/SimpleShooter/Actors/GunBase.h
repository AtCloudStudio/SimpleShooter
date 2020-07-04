// Copyright @CloudStudio 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunBase.generated.h"

class APlayerShooter;
class AProjectileBase;

UCLASS()
class SIMPLESHOOTER_API AGunBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AGunBase();
	virtual void Tick(float DeltaTime) override;

	void TriggerPulled();

private:
	// Components
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* GunRoot;
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* GunMesh;
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	// Shoot
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Shoot", meta = (AllowPrivateAccess = "true"))
	float ShootRange = 30000.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Shoot", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDamageType> DamageType;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Shoot", meta = (AllowPrivateAccess = "true"))
	float ShootDamage = 10.0f;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Shoot", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectileBase> ProjectileClass;

	// Effects
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* MuzzleFlash;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* HitEffect;

	APlayerShooter* Player;

	void LaunchProjectile();
	void DrawShootRay();
	void CourseOriginalShootImplementation();

protected:
	virtual void BeginPlay() override;
};