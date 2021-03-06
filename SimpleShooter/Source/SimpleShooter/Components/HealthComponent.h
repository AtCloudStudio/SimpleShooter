// Copyright @CloudStudio 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class AShooterGameModeBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLESHOOTER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	UFUNCTION(BlueprintPure)
	float GetHealth();

	UFUNCTION(BlueprintPure)
	float GetMaxHealth();

	UFUNCTION(BlueprintPure)
	float GetHealthPercentage();

private:	
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float MaxHealth = 100.0f;

	float Health = 0.0f;

	AActor* Owner;

	AShooterGameModeBase* GameModeReference;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};