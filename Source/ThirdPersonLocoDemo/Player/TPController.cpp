#include "TPController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "../Widgets/WidgetWeaponWheel.h"
#include "Kismet/GameplayStatics.h"

void ATPController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
		{
			if (IMC_TPCharacter)
			{
				Subsystem->AddMappingContext(IMC_TPCharacter, 0);
			}
		}
	}

	CreateWeaponWheelWidget();
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
	}
}

void ATPController::ShowWeaponWheel()
{
	SetInputMode(FInputModeGameAndUI());
	SetShowMouseCursor(true);

	SetIgnoreMoveInput(true);
	SetIgnoreLookInput(true);

	if (WidgetWeaponWheel)
	{
		//WidgetWeaponWheel->WeaponWheel_Show();
	}

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.2f);
}

void ATPController::HideWeaponWheel()
{
	if (WidgetWeaponWheel)
	{
		//WidgetWeaponWheel->WeaponWheel_Hide();
	}

	SetInputMode(FInputModeGameOnly());
	SetShowMouseCursor(false);

	SetIgnoreMoveInput(false);
	SetIgnoreLookInput(false);

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
}