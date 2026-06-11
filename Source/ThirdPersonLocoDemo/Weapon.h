#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class UWeaponData;

UCLASS()
class THIRDPERSONLOCODEMO_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();

	virtual void EquipWeapon(APawn* NewOwner);
	virtual void UnEquipWeapon();
	virtual void DropWeapon();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category= "Weapon")
	UWeaponData* WeaponData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon")
	APawn* WeaponOwner;

	
	
};
