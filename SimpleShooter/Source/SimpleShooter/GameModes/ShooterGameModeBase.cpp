// Copyright @CloudStudio 2020

#include "ShooterGameModeBase.h"
#include "SimpleShooter/Characters/EnemyShooter.h"
#include "SimpleShooter/Characters/PlayerShooter.h"
#include "SimpleShooter/PlayerControllers/PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void AShooterGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APlayerShooter>(UGameplayStatics::GetPlayerPawn(this, 0));
	TargetEnemies = GetTargetEnemiesCount();
	PlayerControllerReference = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	HandleGameStart();
}

int32 AShooterGameModeBase::GetTargetEnemiesCount() 
{
	TArray<AActor*> Enemy;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyShooter::StaticClass(), Enemy);

	return Enemy.Num();
}

void AShooterGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Player)
	{
		Player->CharacterDied();
		HandleGameOver(false);
	}
	else if (AEnemyShooter* DeadEnemy = Cast<AEnemyShooter>(DeadActor))
	{
		DeadEnemy->CharacterDied();
		TargetEnemies--;

		if (TargetEnemies == 0)
		{
			HandleGameOver(true);
		}
	}
}

void AShooterGameModeBase::HandleGameStart()
{
	GameStart();

	if (!ensure(PlayerControllerReference)) return;

	PlayerControllerReference->GetPawn()->DisableInput(PlayerControllerReference);

	FTimerHandle PlayerEnableTimer;
	GetWorldTimerManager().SetTimer(
		PlayerEnableTimer, 
		FTimerDelegate::CreateUObject(PlayerControllerReference, &APlayerControllerBase::SetPlayerEnabledState, true), 
		StartDelay, 
		false);
}

void AShooterGameModeBase::HandleGameOver(bool bPlayerWon)
{
	GameOver(bPlayerWon);

	if (!ensure(PlayerControllerReference)) return;

	PlayerControllerReference->SetPlayerEnabledState(false);

	if (!bPlayerWon)
	{
		FTimerHandle GameRestartTimer;
		GetWorldTimerManager().SetTimer(
		GameRestartTimer, 
		PlayerControllerReference, 
		&APlayerControllerBase::RestartLevel, 
		GameRestartDelay);
	}
}