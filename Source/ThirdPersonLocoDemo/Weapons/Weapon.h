#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interaction/Interactable.h"
#include "Weapon.generated.h"

class ABullet;
enum class EWeaponCurrentActiveSocket : uint8;
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
	ETPCWeaponState GetWeaponState();

	virtual void ReloadWeapon();
	virtual void Fire(const FVector& AimHitLocation);

	DECLARE_DELEGATE_ThreeParams(FOnWeaponStatsUpdated, int32, int32, int32);
	FOnWeaponStatsUpdated OnWeaponStatsUpdated;

	
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon")
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon")
	USceneComponent* WeaponMuzzle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interaction")
	UInteractableComponent* InteractableComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UWeaponData> WeaponData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon", meta=(AllowPrivateAccess="true"))
	TSubclassOf<ABullet> BulletClass;

private:
	UFUNCTION()
	void OnInteracted(APawn* Interactor);

	ETPCWeaponState CurrentWeaponState;
};