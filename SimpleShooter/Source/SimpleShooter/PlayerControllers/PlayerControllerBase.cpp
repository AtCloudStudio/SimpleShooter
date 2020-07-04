// Copyright @CloudStudio 2020

#include "PlayerControllerBase.h"

void APlayerControllerBase::SetPlayerEnabledState(bool bSetPlayerEnabled)
{
	if (bSetPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}
}