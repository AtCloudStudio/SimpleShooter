// Copyright @CloudStudio 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

UCLASS()
class SIMPLESHOOTER_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	void SetPlayerEnabledState(bool bIsPlayerEnabled);

	UFUNCTION(BlueprintCallable)
	void ShowPauseMenu();

	UFUNCTION(BlueprintCallable)
	void ClosePauseMenu();

private:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "User Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> HUDClass;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "User Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> PauseMenuClass;

	UUserWidget* HUD;
	UUserWidget* PauseMenu;

protected:
	virtual void BeginPlay() override;
};