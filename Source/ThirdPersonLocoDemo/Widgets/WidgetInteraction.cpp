#include "WidgetInteraction.h"
#include "Components/TextBlock.h"
#include "ThirdPersonLocoDemo/Enums/TPCInteractionEnums.h"

void UWidgetInteraction::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidgetInteraction::SetInteractionText_Key(const FText& Text)
{
	if (InteractionText_Key)
	{
		InteractionText_Key->SetText(Text);
	}
}

void UWidgetInteraction::SetInteractionText_Description(const FText& Text)
{
	if (InteractionText_Description)
	{
		InteractionText_Description->SetText(Text);
	}
}

void UWidgetInteraction::SetWidgetInteractionType(ETPCInteractableType InteractionType)
{
	switch (InteractionType)
	{
		case ETPCInteractableType::Door:
			SetInteractionText_Key(FText::FromString(TEXT("E")));
			SetInteractionText_Description(FText::FromString(TEXT("Open Door")));
			break;

		case ETPCInteractableType::Weapon:
			SetInteractionText_Key(FText::FromString(TEXT("E")));
			SetInteractionText_Description(FText::FromString(TEXT("Pickup Weapon")));
			break;
	}
}
