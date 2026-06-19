#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interaction/Interactable.h"
#include "Weapon.generated.h"

class UWeaponData;
class USkeletalMeshComponent;
class UInteractableComponent;
class APawn;

UCLASS()
class THIRDPERSONLOCODEMO_API AWeapon : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	AWeapon();
	UWeaponData* GetWeaponData() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interaction")
	UInteractableComponent* InteractableComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	UWeaponData* WeaponData;
};