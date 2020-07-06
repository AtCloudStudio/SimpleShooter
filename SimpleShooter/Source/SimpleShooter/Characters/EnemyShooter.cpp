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
}

void AEnemyShooter::HandleDeath() 
{
    Super::HandleDeath();

    GetController()->Destroy();
}

void AEnemyShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}