#pragma once
#include "CoreMinimal.h"
#include "Interactable.h"
#include "InteractableComponent.generated.h"

enum class ETPCInteractableType : uint8;
enum class EWidgetSpace : uint8;

UCLASS()
class THIRDPERSONLOCODEMO_API UInteractableComponent : public UActorComponent , public IInteractable
{
	GENERATED_BODY()

public:
	UInteractableComponent();

	virtual void BeginPlay() override;

	DECLARE_DELEGATE_OneParam(FOnWeaponPicked, AActor*)
	FOnWeaponPicked OnWeaponPicked;
	
	UPROPERTY(EditDefaultsOnly, Category="Interactable")
	ETPCInteractableType InteractableType;
	
	UPROPERTY(EditDefaultsOnly, Category="Interactable_Widget")
	TSubclassOf<class UWidgetInteraction> InteractableWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Interactable_Widget")
	EWidgetSpace WidgetSpace;

	UPROPERTY(EditDefaultsOnly, Category="Interactable_Sphere")
	float InteractableSphereRadius = 50;

	virtual void BeginInteraction_Implementation(APawn* Interactor) override;
	
private:
	UPROPERTY()
	class AActor* ParentActor;
	
	UPROPERTY()
	class UWidgetComponent* InteractableWidgetComponent;

	UPROPERTY()
	class USphereComponent* InteractableSphere;
	
	UFUNCTION()
	void OnInteractableSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnInteractableSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	void CreateInteractableWidget();
	void CreateInteractableSphere();
};