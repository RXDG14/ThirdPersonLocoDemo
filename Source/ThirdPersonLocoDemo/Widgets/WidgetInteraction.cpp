#include "WidgetInteraction.h"
#include "Components/TextBlock.h"

void UWidgetInteraction::SetInteractionText(const FText& Text)
{
	if (InteractionText)
	{
		InteractionText->SetText(Text);
	}
}