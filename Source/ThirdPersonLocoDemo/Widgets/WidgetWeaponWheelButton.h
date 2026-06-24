#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetWeaponWheelButton.generated.h"

class AWeapon;

UCLASS()
class THIRDPERSONLOCODEMO_API UWidgetWeaponWheelButton : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void SetWeaponButtonText(const FText& NewText);
	void SetWeaponButtonWeapon(AWeapon* InWeapon);
	void SetWeaponButtonSelection(bool bSetAsSelected);

	bool GetIsSelected();
	AWeapon* GetWeaponButtonWeapon();

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnWeaponButtonHovered, UWidgetWeaponWheelButton*);
	FOnWeaponButtonHovered OnWeaponButtonHovered;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnWeaponButtonUnHovered, UWidgetWeaponWheelButton*);
	FOnWeaponButtonUnHovered OnWeaponButtonUnHovered;
	
private:
	UFUNCTION()
	void OnButtonHovered();

	UFUNCTION()
	void OnButtonUnHovered();

	UPROPERTY()
	TObjectPtr<AWeapon> Weapon;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UButton> WeaponButton;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UTextBlock> WeaponButtonText;

	FText WeaponButtonOriginalText;
	bool bIsSelected = false;
};