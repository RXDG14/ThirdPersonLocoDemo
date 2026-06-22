#include "Weapon.h"

#include "InventoryComponent.h"
#include "ThirdPersonLocoDemo/Interaction/InteractableComponent.h"
#include "ThirdPersonLocoDemo/Player/TPCharacter.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);
	
	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("InteractableComponent"));
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (InteractableComponent)
	{
		InteractableComponent->OnInteracted.BindUObject(this,&AWeapon::OnInteracted);
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
