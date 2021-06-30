#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

APawnTurret::APawnTurret()
{}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
	if (!PlayerPawn || ReturnDistanceToPlayer() > FireRange)
	{
		return;
	}
	RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::HandleDestruction()
{
	// Call base pawn class HandleDestruction to play effects.
	Super::HandleDestruction();
	Destroy();
}

void APawnTurret::CheckFireCondition()
{
	if (!PlayerPawn || !PlayerPawn->IsPlayerAlive())
	{
		return;
	}
	if (ReturnDistanceToPlayer() <= FireRange )
	{
		//Call base fire;
		Fire();
	}
}

float APawnTurret::ReturnDistanceToPlayer()
{
	if (!PlayerPawn)
	{
		return 0.0f;
	}
	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}




