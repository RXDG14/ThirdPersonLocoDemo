#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetWeaponWheel.generated.h"

UCLASS()
class THIRDPERSONLOCODEMO_API UWidgetWeaponWheel : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void WeaponWheel_Show();
	void WeaponWheel_Hide();

	int32 GetSelectedSlot() const;

protected:
	UPROPERTY(BlueprintReadOnly)
	int32 SelectedSlot;

	// UPROPERTY(meta = (BindWidget))
	// class UImage* ImageBase;
	//
	// UPROPERTY(meta = (BindWidget))
	// class UImage* ImageSlot0;
	//
	// UPROPERTY(meta = (BindWidget))
	// class UImage* ImageSlot1;
	//
	// UPROPERTY(meta = (BindWidget))
	// class UImage* ImageSlot2;
    //    	
	// UPROPERTY(meta = (BindWidget))
	// class UImage* ImageSlot3;
	
private:
	FVector2D WheelCenter;
	//void UpdateSelection();
	//void UpdateSlotVisuals();
};
