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
