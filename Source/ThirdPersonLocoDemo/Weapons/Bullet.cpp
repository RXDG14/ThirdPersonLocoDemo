#include "Bullet.h"

#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ThirdPersonLocoDemo/Player/TPCharacter.h"

ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(SphereComponent);

	SphereComponent->InitSphereRadius(10.f);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionObjectType(ECC_WorldDynamic);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	SphereComponent->SetGenerateOverlapEvents(true);
	
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	BulletMesh->SetupAttachment(SphereComponent);
	BulletMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileComponent->UpdatedComponent = SphereComponent;
	ProjectileComponent->InitialSpeed = 5000.f;
	ProjectileComponent->MaxSpeed = 6000.f;
	ProjectileComponent->bRotationFollowsVelocity = true;
	ProjectileComponent->ProjectileGravityScale = 0.5f;
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&ABullet::OnBulletSphereBeginOverlap);
}

void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABullet::SetBulletDirection(FRotator Direction)
{
	ProjectileComponent->Velocity = Direction.Vector() * ProjectileComponent->InitialSpeed;
}

void ABullet::OnBulletSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Enemy"))
	{
		if (ACharacter* NPC = Cast<ACharacter>(OtherActor))
		{
			USkeletalMeshComponent* Mesh = NPC->GetMesh();

			// First hit: enable ragdoll
			if (!Mesh->IsSimulatingPhysics())
			{
				Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
				Mesh->SetCollisionProfileName(TEXT("Ragdoll"));

				// The Ragdoll profile defaults to Block on WorldDynamic/PhysicsBody,
				// which swallows the bullet's overlap on subsequent shots.
				// Re-assert Overlap so the bullet keeps registering hits.
				Mesh->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
				Mesh->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
				Mesh->SetGenerateOverlapEvents(true);

				Mesh->SetAllBodiesSimulatePhysics(true);

				NPC->GetCharacterMovement()->DisableMovement();
				NPC->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			}

			// Always wake bodies before impulse - bodies can go to sleep between hits
			Mesh->WakeAllRigidBodies();

			// Push the ragdoll
			const FVector Impulse = ProjectileComponent->Velocity * 2.f;

			if (SweepResult.BoneName != NAME_None)
			{
				Mesh->AddImpulseAtLocation(
				   Impulse,
				   SweepResult.ImpactPoint,
				   SweepResult.BoneName
				);
			}
			else
			{
				Mesh->AddImpulse(
				   Impulse,
				   NAME_None,
				   true
				);
			}
		}
	}
	
	UE_LOG(LogTemp,Warning,TEXT("Destroyed bullet"));
	Destroy();
}


