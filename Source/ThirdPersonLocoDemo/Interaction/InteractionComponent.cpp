#include "InteractionComponent.h"
#include "Interactable.h"
#include "InteractableComponent.h"
#include "GameFramework/Pawn.h"

UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

UInteractableComponent* UInteractionComponent::GetCurrentInteractable() const
{
	AActor* ParentActor = GetOwner();
	if (!ParentActor || InteractableComponents.Num() < 1)
		return nullptr;

	float ClosestDistance = FLT_MAX;
	UInteractableComponent* ClosestInteractableComponent = nullptr;

	for (UInteractableComponent* InteractableComponent : InteractableComponents)
	{
		if (!IsValid(InteractableComponent))
			continue;

		AActor* InteractableActor = InteractableComponent->GetOwner();
		if (!IsValid(InteractableActor))
			continue;

		const float DistanceToPlayer = InteractableActor->GetDistanceTo(ParentActor);
		if (DistanceToPlayer < ClosestDistance)
		{
			ClosestDistance = DistanceToPlayer;
			ClosestInteractableComponent = InteractableComponent;
		}
	}

	return ClosestInteractableComponent;
}

void UInteractionComponent::Interact()
{
	CurrentInteractable = GetCurrentInteractable();
	if (!CurrentInteractable)
		return;

	APawn* Interactor = Cast<APawn>(GetOwner());
	if (!Interactor)
		return;

	if (CurrentInteractable->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
	{
		IInteractable::Execute_BeginInteraction(CurrentInteractable, Interactor);
	}
}

void UInteractionComponent::AddInteractable(UInteractableComponent* InteractableToAdd)
{
	if (!IsValid(InteractableToAdd))
		return;

	InteractableComponents.AddUnique(InteractableToAdd);
	CurrentInteractable = GetCurrentInteractable();
}

void UInteractionComponent::RemoveInteractable(UInteractableComponent* InteractableToRemove)
{
	if (!IsValid(InteractableToRemove))
		return;

	InteractableComponents.RemoveSingleSwap(InteractableToRemove);
	CurrentInteractable = GetCurrentInteractable();
}
