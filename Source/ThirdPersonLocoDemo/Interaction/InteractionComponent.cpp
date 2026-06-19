#include "InteractionComponent.h"

#include "Interactable.h"
#include "GameFramework/Pawn.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentInteractable = nullptr;
}

void UInteractionComponent::Interact()
{
	if (!CurrentInteractable)
	{
		return;
	}

	if (CurrentInteractable->Implements<UInteractable>())
	{
		IInteractable::Execute_Interact(CurrentInteractable, Cast<APawn>(GetOwner()));
	}
}

void UInteractionComponent::SetCurrentInteractable(AActor* NewInteractable)
{
	CurrentInteractable = NewInteractable;
}