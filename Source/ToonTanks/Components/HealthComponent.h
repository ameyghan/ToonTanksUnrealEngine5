#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "HealthComponent.generated.h"

class ATankGameModeBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

private:
	UPROPERTY(EditAnywhere)
	float DefaultHealth = 100.f;
	float Health = 0.f;
	ATankGameModeBase* GameModeRef;
};
