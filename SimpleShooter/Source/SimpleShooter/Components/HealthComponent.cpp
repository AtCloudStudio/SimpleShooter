// Copyright @CloudStudio 2020

#include "HealthComponent.h"
#include "SimpleShooter/GameModes/ShooterGameModeBase.h"
#include "Kismet/GameplayStatics.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	GameModeReference = Cast<AShooterGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (!ensure(GetOwner())) return;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, 
		float Damage, 
		const class UDamageType* DamageType, 
		class AController* InstigatedBy, 
		AActor* DamageCauser) 
{
	if (Damage == 0 || Health == 0) return;

	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);

	UE_LOG(LogTemp, Warning, TEXT("%s Health: %f"), *GetOwner()->GetName(), Health);

	if (Health <= 0)
	{
		if (!ensure(GameModeReference)) return;

		GameModeReference->ActorDied(GetOwner());
		UE_LOG(LogTemp, Warning, TEXT("%s died!"), *GetOwner()->GetName());
	}
}

bool UHealthComponent::IsCharacterDead() const
{
	return Health <= 0;
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}