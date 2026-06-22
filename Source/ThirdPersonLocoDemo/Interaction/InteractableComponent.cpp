#include "InteractableComponent.h"

#include "InteractionComponent.h"
#include "../Widgets/WidgetInteraction.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "ThirdPersonLocoDemo/Enums/TPCInteractionEnums.h"
#include "ThirdPersonLocoDemo/Player/TPCharacter.h"

UInteractableComponent::UInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();

	ParentActor = GetOwner();

	CreateInteractableWidget();
	CreateInteractableSphere();
}

void UInteractableComponent::CreateInteractableWidget()
{
	if (!ParentActor || !InteractableWidgetClass || !ParentActor->GetRootComponent())
		return;
	
	InteractableWidgetComponent = NewObject<UWidgetComponent>(ParentActor, TEXT("InteractableWidget"));
	if (!InteractableWidgetComponent)
		return;
	
	InteractableWidgetComponent->SetWidgetClass(InteractableWidgetClass);
	InteractableWidgetComponent->SetWidgetSpace(WidgetSpace);
	InteractableWidgetComponent->SetVisibility(false);

	InteractableWidgetComponent->SetupAttachment(ParentActor->GetRootComponent());
	ParentActor->AddInstanceComponent(InteractableWidgetComponent);
	InteractableWidgetComponent->RegisterComponent();
	InteractableWidgetComponent->InitWidget();

	if (InteractableWidgetComponent->GetWidget())
	{
		auto* InteractableWidget = Cast<UWidgetInteraction>(InteractableWidgetComponent->GetWidget());
		if (InteractableWidget)
		{
			InteractableWidget->SetWidgetInteractionType(InteractableType);
		}	
	}
}

void UInteractableComponent::BeginInteraction_Implementation(APawn* Interactor)
{
	switch (InteractableType)
	{
		case ETPCInteractableType::Weapon:
			OnWeaponPicked.ExecuteIfBound(ParentActor);
			break;
		case ETPCInteractableType::Door:
			break;
	}
	UE_LOG(LogTemp, Warning, TEXT("Interact called on %s by %s"), *GetOwner()->GetName(), *GetNameSafe(Interactor));
}

void UInteractableComponent::OnInteractableSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ATPCharacter::StaticClass()))
	{
		InteractableWidgetComponent->SetVisibility(true);

		if (ATPCharacter* PlayerCharacter = Cast<ATPCharacter>(OtherActor))
		{
			if (UInteractionComponent* InteractionComp = PlayerCharacter->FindComponentByClass<UInteractionComponent>())
			{
				InteractionComp->AddInteractable(this);
				UE_LOG(LogTemp, Warning, TEXT("Added to InteractableComponents List"));
			}
		}
	}
}

void UInteractableComponent::OnInteractableSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(ATPCharacter::StaticClass()))
	{
		InteractableWidgetComponent->SetVisibility(false);

		if (ATPCharacter* PlayerCharacter = Cast<ATPCharacter>(OtherActor))
		{
			if (UInteractionComponent* InteractionComp = PlayerCharacter->FindComponentByClass<UInteractionComponent>())
			{
				InteractionComp->RemoveInteractable(this);
				UE_LOG(LogTemp, Warning, TEXT("Removed from InteractableComponents List"));
			}
		}
	}
}

void UInteractableComponent::CreateInteractableSphere()
{
	if (!ParentActor || !ParentActor->GetRootComponent())
		return;

	InteractableSphere = NewObject<USphereComponent>(ParentActor, TEXT("InteractableSphere"));
	if (!InteractableSphere)
		return;
	
	InteractableSphere->InitSphereRadius(InteractableSphereRadius);
	InteractableSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractableSphere->SetCollisionObjectType(ECC_WorldDynamic);
	InteractableSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractableSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	InteractableSphere->SetGenerateOverlapEvents(true);

	InteractableSphere->SetupAttachment(ParentActor->GetRootComponent());
	ParentActor->AddInstanceComponent(InteractableSphere);
	InteractableSphere->RegisterComponent();

	InteractableSphere->OnComponentBeginOverlap.AddDynamic(this, &UInteractableComponent::OnInteractableSphereBeginOverlap);
	InteractableSphere->OnComponentEndOverlap.AddDynamic(this, &UInteractableComponent::OnInteractableSphereEndOverlap);
}