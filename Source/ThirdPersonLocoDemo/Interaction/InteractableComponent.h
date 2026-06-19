#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/WidgetComponent.h"
#include "InteractableComponent.generated.h"

enum class EWidgetSpace : uint8;
class USphereComponent;
class UWidgetComponent;
class UWidgetInteraction;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THIRDPERSONLOCODEMO_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractableComponent();

	virtual void BeginPlay() override;

	void SetWidgetClass(TSubclassOf<UWidgetInteraction> InWidgetClass);
	void SetWidgetOffset(FVector InOffset);
	void SetInteractionRadius(float InRadius);

	void ShowPrompt();
	void HidePrompt();
	void UpdatePromptText();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction")
	TSubclassOf<UWidgetInteraction> InteractionWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction")
	float InteractionRadius = 60.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction")
	FVector WidgetRelativeLocation = FVector(0.f, 0.f, 0.f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction")
	EWidgetSpace WidgetSpace = EWidgetSpace::Screen;

	UPROPERTY()
	USphereComponent* InteractionSphere;

	UPROPERTY()
	UWidgetComponent* InteractionWidgetComponent;

	UPROPERTY()
	APawn* OverlappingPawn;

	UFUNCTION()
	void OnInteractionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnInteractionSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	void CreateInteractionSphere();
	void CreateInteractionWidget();
	void AttachToOwnerRoot(USceneComponent* NewComponent);
};