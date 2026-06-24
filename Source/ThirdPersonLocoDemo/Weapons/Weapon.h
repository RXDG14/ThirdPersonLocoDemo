#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interaction/Interactable.h"
#include "Weapon.generated.h"

enum class ETPCWeaponState : uint8;
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
	void SetWeaponState(ETPCWeaponState NewWeaponState);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon")
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interaction")
	UInteractableComponent* InteractableComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UWeaponData> WeaponData;

private:
	UFUNCTION()
	void OnInteracted(APawn* Interactor);

	ETPCWeaponState CurrentWeaponState;
};