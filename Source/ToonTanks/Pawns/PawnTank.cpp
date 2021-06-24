#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "MatineeCameraShake.h"

APawnTank::APawnTank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	bIsPlayerAlive = true;

	MoveSpeed = 100.0f;
	RotateSpeed = 100.0f;
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();	

	PlayerControllerRef = Cast<APlayerController>(GetController());
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Rotate();
	Move();

	if (PlayerControllerRef)
	{
		//	Store information about where the cursor has traced in the world 
		//	(Structure containing information about one hit of a trace, such as point of impact and surface normal at that point)
		FHitResult TraceHitresult;
		//	Trace from the location on the screen where the cursor is currently detected into the world space 
		//	and find the resulting location. (Beaming into the world and give us the coordinates)
		PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, TraceHitresult);

		//The location in the world that the trace has hit (The end location that we want the tank turret to look at)
		FVector HitLocation = TraceHitresult.ImpactPoint;

		RotateTurret(HitLocation);
	}
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotationInput);
	PlayerInputComponent->BindAction("Fire",IE_Pressed, this, &APawnTank::Fire);
}

bool APawnTank::IsPlayerAlive()
{
	return bIsPlayerAlive;
}

void APawnTank::CalculateMoveInput(float Value)
{
	MoveDirection = FVector( Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0 );	
}

void APawnTank::CalculateRotationInput(float Value)
{
	float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator  Rotation = FRotator(0, RotateAmount, 0);
	RotationDirection = FQuat(Rotation);
}

void APawnTank::Move()
{
	AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::Rotate()
{
	AddActorLocalRotation(RotationDirection, true);
}

void APawnTank::HandleDestruction()
{
	Super::HandleDestruction();
	bIsPlayerAlive = false;
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}