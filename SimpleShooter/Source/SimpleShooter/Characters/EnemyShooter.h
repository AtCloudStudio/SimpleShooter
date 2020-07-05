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

protected:
	virtual void BeginPlay() override;
	virtual void HandleDeath() override;
};