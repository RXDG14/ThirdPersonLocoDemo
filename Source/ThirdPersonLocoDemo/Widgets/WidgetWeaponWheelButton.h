#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetWeaponWheelButton.generated.h"

UCLASS()
class THIRDPERSONLOCODEMO_API UWidgetWeaponWheelButton : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

};