// Copyright @CloudStudio 2020

#include "ShooterGameModeBase.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"
#include "SimpleShooter/PlayerControllers/PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"

void AShooterGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Get references and set variables
	Player = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerReference = 
        Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	HandleGameStart();
}

void AShooterGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Player)
	{
		//TODO Player->CharacterDestroyed();
		HandleGameOver(false);

		if (!ensure(PlayerControllerReference)) return;

		PlayerControllerReference->SetPlayerEnabledState(false);
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