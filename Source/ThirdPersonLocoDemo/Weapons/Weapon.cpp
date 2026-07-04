#include "Weapon.h"

#include "InventoryComponent.h"
#include "ThirdPersonLocoDemo/Enums/TPCWeaponEnums.h"
#include "ThirdPersonLocoDemo/Interaction/InteractableComponent.h"
#include "ThirdPersonLocoDemo/Player/TPCharacter.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	WeaponMuzzle = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponMuzzle"));
	WeaponMuzzle->SetupAttachment(WeaponMesh);
	
	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("InteractableComponent"));
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (InteractableComponent)
	{
		InteractableComponent->OnInteracted.BindUObject(this,&AWeapon::OnInteracted);
	}

	if (!GetOwner())
	{
		SetWeaponState(ETPCWeaponState::UnEquipped);
	}
	else
	{
		SetWeaponState(ETPCWeaponState::Equipped);
	}
}

void AWeapon::OnInteracted(APawn* Interactor)
{
	ATPCharacter* Character = Cast<ATPCharacter>(Interactor);
	if (!Character)
		return;

	UInventoryComponent* InventoryComp = Character->FindComponentByClass<UInventoryComponent>();

	if (!InventoryComp)
		return;
	
	InventoryComp->PickupWeapon(this);
}

UWeaponData* AWeapon::GetWeaponData() const
{
	return WeaponData;
}

void AWeapon::SetWeaponState(ETPCWeaponState NewWeaponState)
{
	switch (NewWeaponState)
	{
		case ETPCWeaponState::Equipped:
			WeaponMesh->SetSimulatePhysics(false);
			WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			InteractableComponent->SetInteractionMode(false);
			break;

		case ETPCWeaponState::UnEquipped:
			WeaponMesh->SetSimulatePhysics(true);
			WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			WeaponMesh->SetCollisionResponseToAllChannels(ECR_Block);
			WeaponMesh->SetCollisionResponseToChannel(ECC_Pawn,ECR_Ignore);
			WeaponMesh->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
			InteractableComponent->SetInteractionMode(true);
			break;
		
		case ETPCWeaponState::Holstered:
			WeaponMesh->SetSimulatePhysics(false);
			WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			InteractableComponent->SetInteractionMode(false);
		break;
		
		default:
			break;
	}

	CurrentWeaponState = NewWeaponState;
}

ETPCWeaponState AWeapon::GetWeaponState()
{
	return CurrentWeaponState;
}

void AWeapon::ReloadWeapon()
{
	// implemented in child
}

void AWeapon::StartFire(const FVector& AimHitLocation)
{
	// implemented in child
}

// void AWeapon::StopFire()
// {
// 	// implemented in child
// }

