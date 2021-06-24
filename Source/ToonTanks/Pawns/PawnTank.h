#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"

#include "PawnTank.generated.h"

class USpringArmComponent;
class UCameraComponent;
class APlayerController;

UCLASS()
class TOONTANKS_API APawnTank : public ABasePawn
{
	GENERATED_BODY()

public:
	// Constructor
	APawnTank();

	virtual void HandleDestruction() override;
	bool IsPlayerAlive();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	// Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation", meta = (AllowPrivateAccess = "true"))
	float RotateSpeed;
	APlayerController* PlayerControllerRef;
	bool bIsPlayerAlive;
	FVector MoveDirection;
	FQuat RotationDirection;

	// Functions
	void CalculateMoveInput(float Value);
	void CalculateRotationInput(float Value);
	void Move();
	void Rotate();
};
