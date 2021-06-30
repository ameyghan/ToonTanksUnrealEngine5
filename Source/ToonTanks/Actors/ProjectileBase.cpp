#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "MatineeCameraShake.h"

AProjectileBase::AProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ParticleTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Particle"));
	ParticleTrail->SetupAttachment(RootComponent);
	
	ProjectileMovement->InitialSpeed = MovementSpeed;
	ProjectileMovement->MaxSpeed = MovementSpeed;
	
	InitialLifeSpan = 3.0f;
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();
	if (!MyOwner)
	{
		return;
	}

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, DamageType);
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation());
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitShake);
		Destroy();
	}
}
