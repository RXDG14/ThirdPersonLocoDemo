#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetInteraction.generated.h"

class UTextBlock;

UCLASS()
class THIRDPERSONLOCODEMO_API UWidgetInteraction : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetInteractionText(const FText& Text);

protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* InteractionText;
};