#include "HealthComponent.h"
#include "ToonTanks/GameModes/TankGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/UObjectBaseUtility.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();	
	Health = DefaultHealth;
	AGameModeBase* TheGameMode = UGameplayStatics::GetGameMode(GetWorld());
	GameModeRef = Cast<ATankGameModeBase>(TheGameMode);
	
	//when Ontakedamage on owning actor is called this function will be called
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage == 0 || Health <= 0)
	{
		return;
	}
	//setting the health to be the current health - Damage between 0 and default health value
	Health = FMath::Clamp(Health - Damage, 0.0f, DefaultHealth);
	UE_LOG(LogTemp, Warning, TEXT("%s HEALTH %f"), *DamagedActor->GetName(), Health );
	if (Health <= 0 )
	{
		if (GameModeRef)
		{
			GameModeRef->ActorDied(GetOwner());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("HealthComponent has no reference to the GameMode"));
		}
	}
}
