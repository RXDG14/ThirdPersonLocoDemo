#include "Bullet.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

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
	UE_LOG(LogTemp,Warning,TEXT("Destroyed bullet"));
	Destroy();
}


