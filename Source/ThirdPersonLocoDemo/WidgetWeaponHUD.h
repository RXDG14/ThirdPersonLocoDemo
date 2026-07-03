#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetWeaponHUD.generated.h"

UCLASS()
class THIRDPERSONLOCODEMO_API UWidgetWeaponHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void SetCurrentAmmoInClip(int32 Amount);
	void SetAmmoClipSize(int32 Amount);
	void SetTotalRemainingSpareAmmo(int32 Amount);
	void SetWeaponImage(UTexture2D* Texture);
	void SetWeaponHUDVisiblity(bool value);
	
private:
	UPROPERTY(meta=(BindWidget))
	class UTextBlock* CurrentAmmoInClipText;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* AmmoClipSizeText;

	UPROPERTY(meta=(BindWidget))
	class UTextBlock* TotalRemainingSpareAmmoText;

	UPROPERTY(meta=(BindWidget))
	class UImage* WeaponImage;
};
