// Copyright @CloudStudio 2020

#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleShooter/GameModes/ShooterGameModeBase.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	GameModeReference = Cast<AShooterGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	Owner = GetOwner();

	if (!ensure(Owner)) return;

	Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) 
{
	if (Damage == 0 || Health == 0) return;

	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);

	if (Health <= 0)
	{
		if (!ensure(GameModeReference)) return;

		GameModeReference->ActorDied(Owner);
	}
	UE_LOG(LogTemp, Warning, TEXT("%s Health: %f"), *Owner->GetName(), Health);
}