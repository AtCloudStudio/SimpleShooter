// Copyright @CloudStudio 2020

#include "PlayerControllerBase.h"
#include "Blueprint/UserWidget.h"

void APlayerControllerBase::BeginPlay() 
{
	Super::BeginPlay();
}

void APlayerControllerBase::SetPlayerEnabledState(bool bSetPlayerEnabled)
{
	if (!GetPawn()) return;

	if (bSetPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}
}

void APlayerControllerBase::ShowHUD()
{
	HUD = CreateWidget(this, HUDClass);

	if (!ensure(HUD)) return;

	HUD->AddToViewport();
}

void APlayerControllerBase::HideHUD()
{
	if (!ensure(HUD)) return;

	HUD->RemoveFromParent();
}

void APlayerControllerBase::ShowPauseMenu() 
{
	PauseMenu = CreateWidget(this, PauseMenuClass);

	if (!ensure(PauseMenu || HUD)) return;

	SetPause(true);
	PauseMenu->AddToViewport();
	SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = true;
	HUD->SetVisibility(ESlateVisibility::Hidden);
}

void APlayerControllerBase::ClosePauseMenu() 
{
	if (!ensure(PauseMenu || HUD)) return;
	
	SetPause(false);
	PauseMenu->RemoveFromParent();
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
	HUD->SetVisibility(ESlateVisibility::Visible);
}