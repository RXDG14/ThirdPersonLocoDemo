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

	virtual void EquipWeapon(APawn* NewOwner, int32 WeaponSlot);
	virtual void UnEquipWeapon(int32 WeaponSlot);
	virtual void DropWeapon(int32 WeaponSlot);
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapons", meta = (AllowPrivateAccess = "true"))
	class AWeapon* CurrentWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapons", meta = (AllowPrivateAccess = "true"))
	int CurrentActiveWeaponSlot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapons", meta = (AllowPrivateAccess = "true"))
	int MaxWeaponSlots;
	
	///////////////////////////////////////////////////////////////////////////////////////////

	
		
};
