#include "TPCharacter.h"

#include "CharacterTrajectoryComponent.h" 
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TPCMovementMode.h"
#include "GameFramework/CharacterMovementComponent.h"

ATPCharacter::ATPCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	TrajectoryComponent = CreateDefaultSubobject<UCharacterTrajectoryComponent>(TEXT("CharacterTrajectoryComponent"));
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetRootComponent());

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	PlayerCamera->SetupAttachment(SpringArm);
}

void ATPCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	SetTPCMovementMode(ETPCMovementMode::Walk);
}

void ATPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EIC = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ATPCharacter::MovePlayer);
		EIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &ATPCharacter::Look);
		EIC->BindAction(IA_Jump, ETriggerEvent::Started, this, &ATPCharacter::Jump);
		EIC->BindAction(IA_Crouch, ETriggerEvent::Started, this, &ATPCharacter::ToggleCrouch);
		EIC->BindAction(IA_Walk, ETriggerEvent::Started, this, &ATPCharacter::ToggleWalkJog);
		EIC->BindAction(IA_Sprint, ETriggerEvent::Started, this, &ATPCharacter::StartSprinting);
		EIC->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &ATPCharacter::StopSprinting);
	}
}

void ATPCharacter::MovePlayer(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void ATPCharacter::Look(const FInputActionValue& Value)
{
	FVector2d LookAxisVector = Value.Get<FVector2D>();

	AddControllerPitchInput(LookAxisVector.Y * 0.5f);
	AddControllerYawInput(LookAxisVector.X * 0.5f);
}

void ATPCharacter::StartSprinting()
{
	SetTPCMovementMode(ETPCMovementMode::Sprint);
}

void ATPCharacter::StopSprinting()
{
	SetTPCMovementMode(ETPCMovementMode::Jog);
}

void ATPCharacter::ToggleCrouch()
{
	SetTPCMovementMode(ETPCMovementMode::Crouch);
}

void ATPCharacter::ToggleWalkJog()
{
	SetTPCMovementMode(CurrentMovementMode == ETPCMovementMode::Walk ? ETPCMovementMode::Jog : ETPCMovementMode::Walk);
}

void ATPCharacter::SetTPCMovementMode(ETPCMovementMode NewMovementMode)
{
	if (NewMovementMode == ETPCMovementMode::Walk)
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		CurrentMovementMode = NewMovementMode;
	}

	if (NewMovementMode == ETPCMovementMode::Jog)
	{
		GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
		CurrentMovementMode = NewMovementMode;
		bIsTPCCrouched = false;
	}

	if (NewMovementMode == ETPCMovementMode::Sprint)
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
		CurrentMovementMode = NewMovementMode;
		bIsTPCCrouched = false;
	}

	if (NewMovementMode == ETPCMovementMode::Crouch)
	{
		if (bIsTPCCrouched)
		{
			bIsTPCCrouched = false;
			SetTPCMovementMode(ETPCMovementMode::Walk);
		}
		else
		{
			bIsTPCCrouched = true;
			GetCharacterMovement()->MaxWalkSpeed = CrouchSpeed;
			CurrentMovementMode = NewMovementMode;
		}
	}
}
