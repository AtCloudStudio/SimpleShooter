// Copyright @CloudStudio 2020

#include "EnemyShooter.h"
#include "PlayerShooter.h"
#include "Kismet/GameplayStatics.h"

AEnemyShooter::AEnemyShooter() 
{ 
    PrimaryActorTick.bCanEverTick = false;
}

void AEnemyShooter::BeginPlay() 
{
    Super::BeginPlay();
    
    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, 
        &AEnemyShooter::CheckFireCondition, FireRate, true, false);

    Player = Cast<APlayerShooter>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AEnemyShooter::CheckFireCondition() 
{
    if (!ensure(Player) || Player->IsCharacterDead()) return;

    if ((Player->GetActorLocation() - GetActorLocation()).Size() <= FireRange)
    {
        Shoot();
    }
}

void AEnemyShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}