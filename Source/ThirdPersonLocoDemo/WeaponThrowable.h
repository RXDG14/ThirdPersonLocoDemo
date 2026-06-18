#pragma once
#include "CoreMinimal.h"
#include "Weapons/Weapon.h"
#include "WeaponThrowable.generated.h"

UCLASS()
class THIRDPERSONLOCODEMO_API AWeaponThrowable : public AWeapon
{
	GENERATED_BODY()

public:
	virtual void Throw();
};
