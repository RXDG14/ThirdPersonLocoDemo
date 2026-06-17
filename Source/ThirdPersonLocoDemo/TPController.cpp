#include "TPController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "WidgetWeaponWheel.h"

void ATPController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(IMC_TPCharacter, 0);
	}

	CreateWeaponWheelWidget();
}

void ATPController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EIC = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// do bindings here for UI
		EIC->BindAction(IA_WeaponWheel,ETriggerEvent::Started,this,&ATPController::ShowWeaponWheel);
		EIC->BindAction(IA_WeaponWheel,ETriggerEvent::Completed,this,&ATPController::HideWeaponWheel);
	}
}

void ATPController::CreateWeaponWheelWidget()
{
	if (WeaponWheelClass)
	{
		WidgetWeaponWheel = CreateWidget<UWidgetWeaponWheel>(this, WeaponWheelClass);

		if (WidgetWeaponWheel)
		{
			WidgetWeaponWheel->AddToViewport();
			WidgetWeaponWheel->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void ATPController::ShowWeaponWheel()
{
	const FInputModeGameAndUI InputModeGameAndUI;
	SetInputMode(InputModeGameAndUI);
	SetShowMouseCursor(true);

	SetIgnoreMoveInput(true);
	SetIgnoreLookInput(true);

	if (WidgetWeaponWheel)
	{
		WidgetWeaponWheel->WeaponWheel_Show();
	}
}

void ATPController::HideWeaponWheel()
{
	const FInputModeGameOnly InputModeGameOnly;
	SetInputMode(InputModeGameOnly);
	SetShowMouseCursor(false);

	SetIgnoreMoveInput(false);
	SetIgnoreLookInput(false);

	if (WidgetWeaponWheel)
	{
		WidgetWeaponWheel->WeaponWheel_Hide();
		//if (WidgetWeaponWheel->GetSelectedSlot() > -1)
		//{
			//SelectedWeaponSlot = WidgetWeaponWheel->GetSelectedSlot();
			//OnWeaponWheelHid.Broadcast(SelectedWeaponSlot);
		//}
	}
}
