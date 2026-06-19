#include "InteractableComponent.h"

#include "Interactable.h"
#include "InteractionComponent.h"
#include "../Widgets/WidgetInteraction.h"

#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/SceneComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Pawn.h"

UInteractableComponent::UInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	InteractionSphere = nullptr;
	InteractionWidgetComponent = nullptr;
	OverlappingPawn = nullptr;
}

void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();

	CreateInteractionSphere();
	CreateInteractionWidget();

	HidePrompt();
}

void UInteractableComponent::SetWidgetClass(TSubclassOf<UWidgetInteraction> InWidgetClass)
{
	InteractionWidgetClass = InWidgetClass;

	if (InteractionWidgetComponent)
	{
		InteractionWidgetComponent->SetWidgetClass(InteractionWidgetClass);
		InteractionWidgetComponent->InitWidget();
		UpdatePromptText();
	}
}

void UInteractableComponent::SetWidgetOffset(FVector InOffset)
{
	WidgetRelativeLocation = InOffset;

	if (InteractionWidgetComponent)
	{
		InteractionWidgetComponent->SetRelativeLocation(WidgetRelativeLocation);
	}
}

void UInteractableComponent::SetInteractionRadius(float InRadius)
{
	InteractionRadius = InRadius;

	if (InteractionSphere)
	{
		InteractionSphere->SetSphereRadius(InteractionRadius);
	}
}

void UInteractableComponent::CreateInteractionSphere()
{
	AActor* OwnerActor = GetOwner();
	if (!OwnerActor || InteractionSphere)
	{
		return;
	}

	USceneComponent* OwnerRoot = OwnerActor->GetRootComponent();
	if (!OwnerRoot)
	{
		return;
	}

	InteractionSphere = NewObject<USphereComponent>(OwnerActor, TEXT("InteractionSphere"));
	if (!InteractionSphere)
	{
		return;
	}

	InteractionSphere->InitSphereRadius(InteractionRadius);
	InteractionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionSphere->SetCollisionObjectType(ECC_WorldDynamic);
	InteractionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	InteractionSphere->SetGenerateOverlapEvents(true);

	InteractionSphere->SetupAttachment(OwnerRoot);
	OwnerActor->AddInstanceComponent(InteractionSphere);
	InteractionSphere->RegisterComponent();

	InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &UInteractableComponent::OnInteractionSphereBeginOverlap);
	InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &UInteractableComponent::OnInteractionSphereEndOverlap);
}

void UInteractableComponent::CreateInteractionWidget()
{
	AActor* OwnerActor = GetOwner();
	if (!OwnerActor || InteractionWidgetComponent)
	{
		return;
	}

	USceneComponent* OwnerRoot = OwnerActor->GetRootComponent();
	if (!OwnerRoot)
	{
		return;
	}

	InteractionWidgetComponent = NewObject<UWidgetComponent>(OwnerActor, TEXT("InteractionWidgetComponent"));
	if (!InteractionWidgetComponent)
	{
		return;
	}

	InteractionWidgetComponent->SetWidgetClass(InteractionWidgetClass);
	InteractionWidgetComponent->SetWidgetSpace(WidgetSpace);
	InteractionWidgetComponent->SetDrawAtDesiredSize(true);
	InteractionWidgetComponent->SetVisibility(false);
	InteractionWidgetComponent->SetRelativeLocation(WidgetRelativeLocation);

	InteractionWidgetComponent->SetupAttachment(OwnerRoot);
	OwnerActor->AddInstanceComponent(InteractionWidgetComponent);
	InteractionWidgetComponent->RegisterComponent();
	InteractionWidgetComponent->InitWidget();

	UpdatePromptText();
}

void UInteractableComponent::UpdatePromptText()
{
	if (!InteractionWidgetComponent)
	{
		return;
	}

	if (!GetOwner() || !GetOwner()->Implements<UInteractable>())
	{
		return;
	}

	if (UUserWidget* UserWidget = InteractionWidgetComponent->GetUserWidgetObject())
	{
		if (UWidgetInteraction* PromptWidget = Cast<UWidgetInteraction>(UserWidget))
		{
			PromptWidget->SetInteractionText(IInteractable::Execute_GetInteractionText(GetOwner()));
		}
	}
}

void UInteractableComponent::ShowPrompt()
{
	if (InteractionWidgetComponent)
	{
		UpdatePromptText();
		InteractionWidgetComponent->SetVisibility(true);
	}
}

void UInteractableComponent::HidePrompt()
{
	if (InteractionWidgetComponent)
	{
		InteractionWidgetComponent->SetVisibility(false);
	}
}

void UInteractableComponent::OnInteractionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* Pawn = Cast<APawn>(OtherActor);
	if (!Pawn)
	{
		return;
	}

	OverlappingPawn = Pawn;

	if (UInteractionComponent* InteractionComponent = Pawn->FindComponentByClass<UInteractionComponent>())
	{
		InteractionComponent->SetCurrentInteractable(GetOwner());
	}

	ShowPrompt();
}

void UInteractableComponent::OnInteractionSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APawn* Pawn = Cast<APawn>(OtherActor);
	if (!Pawn)
	{
		return;
	}

	if (OverlappingPawn == Pawn)
	{
		OverlappingPawn = nullptr;
	}

	if (UInteractionComponent* InteractionComponent = Pawn->FindComponentByClass<UInteractionComponent>())
	{
		if (InteractionComponent->GetCurrentInteractable() == GetOwner())
		{
			InteractionComponent->SetCurrentInteractable(nullptr);
		}
	}

	HidePrompt();
}