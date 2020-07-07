// Copyright @CloudStudio 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AProjectileBase;
class UHealthComponent;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AShooterCharacter();
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintPure)
	bool IsCharacterDead();

	void CharacterDied();

	FHitResult& Aim(FHitResult& Hit);

	void Shoot();

private:

	// Components
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* GunMesh;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;

	// Shoot
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Shoot", meta = (AllowPrivateAccess = "true"))
	float ShootRange = 30000.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Shoot", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectileBase> ProjectileClass;

	// Effects
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	USoundBase* DeathSound;

	bool bIsDead;

protected:

	virtual void BeginPlay() override;

	virtual void HandleDeath();
};