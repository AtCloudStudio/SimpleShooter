// Copyright @CloudStudio 2020

#include "PlayerControllerBase.h"
#include "Blueprint/UserWidget.h"

void APlayerControllerBase::BeginPlay() 
{
	Super::BeginPlay();

	HUD = CreateWidget(this, HUDClass);
	PauseMenu = CreateWidget(this, PauseMenuClass);
}

void APlayerControllerBase::SetPlayerEnabledState(bool bSetPlayerEnabled)
{
	if (!ensure(GetPawn())) return;
	
	if (bSetPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
		HUD->AddToViewport();
	}
	else
	{
		GetPawn()->DisableInput(this);
		HUD->SetVisibility(ESlateVisibility::Hidden);
	}
}

void APlayerControllerBase::ShowPauseMenu() 
{
	if (!ensure(HUD || PauseMenu)) return;

	HUD->SetVisibility(ESlateVisibility::Hidden);
	SetPause(true);
	PauseMenu->AddToViewport();
	SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = true;
}

void APlayerControllerBase::ClosePauseMenu() 
{
	if (!ensure(HUD || PauseMenu)) return;
	
	SetPause(false);
	PauseMenu->RemoveFromParent();
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
	HUD->SetVisibility(ESlateVisibility::Visible);
}