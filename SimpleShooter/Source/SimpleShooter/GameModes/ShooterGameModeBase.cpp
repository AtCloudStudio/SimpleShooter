// Copyright @CloudStudio 2020

#include "ShooterGameModeBase.h"
#include "SimpleShooter/Characters/EnemyShooter.h"
#include "SimpleShooter/Characters/PlayerShooter.h"
#include "SimpleShooter/PlayerControllers/PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"

void AShooterGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APlayerShooter>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerReference = 
        Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	HandleGameStart();
}

void AShooterGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Player)
	{
		Player->CharacterDied();
		HandleGameOver(false);

		if (!ensure(PlayerControllerReference)) return;

		PlayerControllerReference->SetPlayerEnabledState(false);
	}
	else if (AEnemyShooter* DeadEnemy = Cast<AEnemyShooter>(DeadActor))
	{
		DeadEnemy->CharacterDied();
		// TODO Disable enemy
	}
}

void AShooterGameModeBase::HandleGameStart()
{
	GameStart();

	if (!ensure(PlayerControllerReference)) return;

	PlayerControllerReference->SetPlayerEnabledState(false);

	FTimerHandle PlayerEnablehandle;
	GetWorld()->GetTimerManager().SetTimer(
		PlayerEnablehandle, 
		FTimerDelegate::
            CreateUObject(PlayerControllerReference, &APlayerControllerBase::SetPlayerEnabledState, true), 
		StartDelay, 
		false);
}

void AShooterGameModeBase::HandleGameOver(bool PlayerWon)
{
	GameOver(PlayerWon);
}