#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONLOCODEMO_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void EquipWeapon(APawn* NewOwner);
	virtual void EquipWeaponFromInventory(class AWeapon* Weapon);
	virtual void UnEquipWeapon(class AWeapon* Weapon);
	virtual void DropWeapon(class AWeapon* Weapon);

	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapons", meta = (AllowPrivateAccess = "true"))
	class AWeapon* CurrentWeapon;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapons", meta = (AllowPrivateAccess = "true"))
	TArray<AWeapon*> WeaponsInInventory;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapons", meta = (AllowPrivateAccess = "true"))
	int32 MaxWeapons = 4;
	///////////////////////////////////////////////////////////////////////////////////////////

	
		
};
