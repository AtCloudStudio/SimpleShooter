// Copyright @CloudStudio 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterGameModeBase.generated.h"

class AEnemyShooter;
class APlayerShooter;
class APlayerControllerBase;

UCLASS()
class SIMPLESHOOTER_API AShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);

	void ActorDied(AActor* DeadActor);

private:
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Characters", meta = (AllowPrivateAccess = "true"))
	APlayerShooter* Player;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Game Loop", meta = (AllowPrivateAccess = "true"))
	int32 StartDelay = 4;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Game Loop", meta = (AllowPrivateAccess = "true"))
	int32 GameRestartDelay = 5;

	int32 TargetEnemies = 0;

	APlayerControllerBase* PlayerControllerReference;

	int32 GetTargetEnemiesCount();

	void HandleGameStart();
	
	void HandleGameOver(bool PlayerWon);
	
protected:
	virtual void BeginPlay() override;
};