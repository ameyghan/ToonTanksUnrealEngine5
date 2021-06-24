#include "PlayerControllerBase.h"

void APlayerControllerBase::SetPlayerEnableState(bool bIsPlayerEnabled)
{
	if (bIsPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}
	bShowMouseCursor = bIsPlayerEnabled;
}
