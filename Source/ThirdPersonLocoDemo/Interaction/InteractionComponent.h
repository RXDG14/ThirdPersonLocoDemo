#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THIRDPERSONLOCODEMO_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractionComponent();

	void Interact();
	void SetCurrentInteractable(AActor* NewInteractable);

	AActor* GetCurrentInteractable() const { return CurrentInteractable; }

protected:
	UPROPERTY()
	AActor* CurrentInteractable;
};