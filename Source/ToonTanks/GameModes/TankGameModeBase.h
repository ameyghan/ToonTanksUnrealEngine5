#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "TankGameModeBase.generated.h"

class APawnTurret;
class APawnTank;
class APlayerControllerBase;

UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	//Constructor
	ATankGameModeBase();

	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;

	// Variables
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
	int32 StartDelay;
	
	// Will be implemented in Blueprints. Will not be defined in C++
	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool PlayerWon);

private:
	APawnTank* PlayerTank;
	int32 TargetTurrets = 0;
	APlayerControllerBase* PlayerControllerRef;
	void HandleGameStart();
	void HandleGamveOver(bool PlayerWon);
	int32 GetTargetTurretCount();
};
