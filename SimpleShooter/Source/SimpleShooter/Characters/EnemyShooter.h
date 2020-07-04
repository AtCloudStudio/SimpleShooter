// Copyright @CloudStudio 2020

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"
#include "EnemyShooter.generated.h"

class APlayerShooter;

UCLASS()
class SIMPLESHOOTER_API AEnemyShooter : public AShooterCharacter
{
	GENERATED_BODY()
	
public:
	AEnemyShooter();
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRange = 1000.0f;

	FTimerHandle FireRateTimerHandle;

	APlayerShooter* Player;

	void CheckFireCondition();

protected:
	virtual void BeginPlay() override;
};