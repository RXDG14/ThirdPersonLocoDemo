#include "TPController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "../Widgets/WidgetWeaponWheel.h"
#include "Kismet/GameplayStatics.h"
#include "ThirdPersonLocoDemo/Weapons/InventoryComponent.h"

void ATPController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
		{
			if (IMC_TPCharacter)
			{
				Subsystem->AddMappingContext(IMC_TPCharacter, 1); // high number = high priority
				Subsystem->AddMappingContext(IMC_WeaponWheel, 0);
			}
		}
	}
}

void ATPController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (IA_WeaponWheel)
		{
			EIC->BindAction(IA_WeaponWheel, ETriggerEvent::Started, this, &ATPController::ShowWeaponWheel);
			EIC->BindAction(IA_WeaponWheel, ETriggerEvent::Completed, this, &ATPController::HideWeaponWheel);
		}
	}
}

void ATPController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	CreateWeaponWheelWidget();
}

void ATPController::CreateWeaponWheelWidget()
{
	if (!WidgetWeaponWheelClass)
	{
		return;
	}

	WidgetWeaponWheel = CreateWidget<UWidgetWeaponWheel>(this, WidgetWeaponWheelClass);

	if (WidgetWeaponWheel)
	{
		WidgetWeaponWheel->AddToViewport();
		WidgetWeaponWheel->SetVisibility(ESlateVisibility::Hidden);

		if (UInventoryComponent* InventoryComp = GetPawn()->FindComponentByClass<UInventoryComponent>())
		{
			WidgetWeaponWheel->SetInventoryComponent(InventoryComp);
		}
	}
}

void ATPController::ShowWeaponWheel()
{
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
		{
			Subsystem->RemoveMappingContext(IMC_TPCharacter);
		}
	}

	if (WidgetWeaponWheel)
	{
		WidgetWeaponWheel->WeaponWheel_Show();
	}

	SetInputMode(FInputModeGameAndUI());
	SetShowMouseCursor(true);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.2f);
}

void ATPController::HideWeaponWheel()
{
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
		{
			Subsystem->AddMappingContext(IMC_TPCharacter, 1);
		}
	}

	if (WidgetWeaponWheel)
	{
		WidgetWeaponWheel->WeaponWheel_Hide();
	}

	SetInputMode(FInputModeGameOnly());
	SetShowMouseCursor(false);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
}