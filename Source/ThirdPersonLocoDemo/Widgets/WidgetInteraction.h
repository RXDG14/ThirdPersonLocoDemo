#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetInteraction.generated.h"

enum class ETPCInteractableType : uint8;
class UTextBlock;

UCLASS()
class THIRDPERSONLOCODEMO_API UWidgetInteraction : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SetInteractionText_Key(const FText& Text);

	UFUNCTION()
	void SetInteractionText_Description(const FText& Text);

	void SetWidgetInteractionType(ETPCInteractableType InteractionType);
protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* InteractionText_Key;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* InteractionText_Description;
	
};