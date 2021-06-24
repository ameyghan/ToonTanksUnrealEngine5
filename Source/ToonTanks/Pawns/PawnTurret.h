#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"

#include "PawnTurret.generated.h"

class APawnTank;

UCLASS()
class TOONTANKS_API APawnTurret : public ABasePawn
{
	GENERATED_BODY()

public:
	//Constructor
	APawnTurret();
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDestruction() override;

protected:
	virtual void BeginPlay() override;

private:
	// Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRange;
	
	FTimerHandle FireRateTimerHandle;
	APawnTank* PlayerPawn;

	// Functions
	void CheckFireCondition();
	float ReturnDistanceToPlayer();
	
};
