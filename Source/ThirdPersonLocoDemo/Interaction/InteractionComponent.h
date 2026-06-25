#pragma once
#include "CoreMinimal.h"
#include "InteractionComponent.generated.h"

class UInteractableComponent;

UCLASS()
class THIRDPERSONLOCODEMO_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractionComponent();
	
	void Interact();
	void AddInteractable(UInteractableComponent* InteractableToAdd);
	void RemoveInteractable(UInteractableComponent* InteractableToRemove);
	bool GetCanInteract();
	
private:
	UInteractableComponent* GetCurrentInteractable() const;

	UPROPERTY()
	TArray<UInteractableComponent*> InteractableComponents;

	UPROPERTY()
	UInteractableComponent* CurrentInteractable;

};