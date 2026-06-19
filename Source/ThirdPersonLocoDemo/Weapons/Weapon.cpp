#include "Weapon.h"

#include "../Weapons/WeaponData.h"
#include "../Weapons/InventoryComponent.h"
#include "../Interaction/InteractableComponent.h"

#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "Components/SceneComponent.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	WeaponMesh->SetGenerateOverlapEvents(false);

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("InteractableComponent"));

	WeaponOwner = nullptr;
}

UWeaponData* AWeapon::GetWeaponData() const
{
	return WeaponData;
}

void AWeapon::SetWeaponOwner(APawn* NewOwner)
{
	WeaponOwner = NewOwner;
	SetOwner(NewOwner);
}

void AWeapon::EnableWorldCollision()
{
	if (WeaponMesh)
	{
		WeaponMesh->SetSimulatePhysics(true);
		WeaponMesh->SetEnableGravity(true);
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		WeaponMesh->SetCollisionProfileName(TEXT("PhysicsActor"));
	}
}

void AWeapon::DisableWorldCollision()
{
	if (WeaponMesh)
	{
		WeaponMesh->SetSimulatePhysics(false);
		WeaponMesh->SetEnableGravity(false);
		WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AWeapon::Interact_Implementation(APawn* InteractingPawn)
{
	if (!InteractingPawn)
	{
		return;
	}

	if (UInventoryComponent* Inventory = InteractingPawn->FindComponentByClass<UInventoryComponent>())
	{
		Inventory->PickupWeapon(this);
	}
}

FText AWeapon::GetInteractionText_Implementation() const
{
	if (WeaponData)
	{
		return FText::Format(FText::FromString(TEXT("E")), WeaponData->WeaponName);
	}

	return FText::FromString(TEXT("E"));
}