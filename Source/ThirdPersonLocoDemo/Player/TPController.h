#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TPController.generated.h"

class UWidgetWeaponHUD;
class UInputMappingContext;
class UInputAction;
class UWidgetWeaponWheel;

UCLASS()
class THIRDPERSONLOCODEMO_API ATPController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	// Input
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputMappingContext* IMC_TPCharacter;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputMappingContext* IMC_WeaponWheel;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* IA_WeaponWheel;
	
	// UI
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UWidgetWeaponWheel> WidgetWeaponWheelClass;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UWidgetWeaponHUD> WidgetWeaponHUDClass;
	
	UPROPERTY()
	UWidgetWeaponWheel* WidgetWeaponWheel;

	UPROPERTY()
	UWidgetWeaponHUD* WidgetWeaponHUD;

private:
	void CreateWeaponWheelWidget();
	void CreateWeaponHUDWidget();
	void ShowWeaponWheel();
	void HideWeaponWheel();
};