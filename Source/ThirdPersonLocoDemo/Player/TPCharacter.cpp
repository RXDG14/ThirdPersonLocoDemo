#include "TPCharacter.h"
#include "CharacterTrajectoryComponent.h" 
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "../Weapons/InventoryComponent.h"
#include "CameraHandlerComponent.h"
#include "../Interaction/InteractionComponent.h"
#include "../Enums/TPCPlayerEnums.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

ATPCharacter::ATPCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCharacterMovement()->MaxAcceleration = 600.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1200.f;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 180.0f, 0.0f);

	bUseControllerRotationYaw = false;
	
	TrajectoryComponent = CreateDefaultSubobject<UCharacterTrajectoryComponent>(TEXT("CharacterTrajectoryComponent"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->bUsePawnControlRotation = true;

	CameraHandler = CreateDefaultSubobject<UCameraHandlerComponent>(TEXT("CameraHandler"));
	
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	PlayerCamera->SetupAttachment(SpringArm);

	CameraHandler->InitializeCamera(SpringArm,PlayerCamera);

	BackPackMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackPack"));
	BackPackMesh->SetupAttachment(GetMesh(), TEXT("BagpackSocket"));
}

void ATPCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	SetTPCMovementMode(ETPCPlayerMovementMode::Walk);
	SetTPCMotionMatchingType(ETPCMotionMatchingType::With_OrientRotationToMovement);
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
		EIC->BindAction(IA_Interact, ETriggerEvent::Started, this, &ATPCharacter::Interact);
		EIC->BindAction(IA_MMTypeSwitch, ETriggerEvent::Started, this, &ATPCharacter::ToggleMotionMatchingType);
		EIC->BindAction(IA_CameraTypeSwitch, ETriggerEvent::Started, this, &ATPCharacter::ToggleCameraType);
		EIC->BindAction(IA_Sprint, ETriggerEvent::Started, this, &ATPCharacter::StartSprinting);
		EIC->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &ATPCharacter::StopSprinting);
		EIC->BindAction(IA_Drop, ETriggerEvent::Started, this, &ATPCharacter::DropWeapon);
		EIC->BindAction(IA_Holster, ETriggerEvent::Started, this, &ATPCharacter::HolsterWeapon);
		EIC->BindAction(IA_Aim, ETriggerEvent::Started, this, &ATPCharacter::StartAiming);
		EIC->BindAction(IA_Aim, ETriggerEvent::Completed, this, &ATPCharacter::StopAiming);
		EIC->BindAction(IA_Attack, ETriggerEvent::Started, this, &ATPCharacter::DoAttack);
		EIC->BindAction(IA_Reload, ETriggerEvent::Started, this, &ATPCharacter::DoReload);
	}
}

void ATPCharacter::Notify_OnWeaponHolstered()
{
	if (InventoryComponent)
	{
		InventoryComponent->HolsterCurrentlyEquippedWeapon();
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

	if (GetIsAiming())
	{
		AddControllerPitchInput(LookAxisVector.Y * MovementSettings.LookSpeedAiming);
		AddControllerYawInput(LookAxisVector.X * MovementSettings.LookSpeedAiming);
	}
	else
	{
		AddControllerPitchInput(LookAxisVector.Y * MovementSettings.LookSpeed);
		AddControllerYawInput(LookAxisVector.X * MovementSettings.LookSpeed);
	}
}

void ATPCharacter::Interact(const FInputActionValue& Value)
{
	if (InteractionComponent->GetCanInteract())
	{
		if (AM_Pickup)
		{
			PlayAnimationMontage(AM_Pickup);
		}
		InteractionComponent->Interact();
	}
}

void ATPCharacter::DropWeapon(const FInputActionValue& Value)
{
	InventoryComponent->DropCurrentlyEquippedWeapon();
}

void ATPCharacter::HolsterWeapon(const FInputActionValue& Value)
{
	SetTPCAnimationState(ETPCAnimationState::Unarmed);
	if (AM_Holster && GetHasWeaponInHand())
	{
		PlayAnimationMontage(AM_Holster);
	}
}

void ATPCharacter::StartSprinting()
{
	SetTPCMovementMode(ETPCPlayerMovementMode::Sprint);
}

void ATPCharacter::StopSprinting()
{
	SetTPCMovementMode(ETPCPlayerMovementMode::Jog);
}

void ATPCharacter::ToggleCrouch()
{
	SetTPCMovementMode(ETPCPlayerMovementMode::Crouch);
}

void ATPCharacter::ToggleWalkJog()
{
	SetTPCMovementMode(CurrentMovementMode == ETPCPlayerMovementMode::Walk ? ETPCPlayerMovementMode::Jog : ETPCPlayerMovementMode::Walk);
}

void ATPCharacter::ToggleMotionMatchingType()
{
	if (!GetIsAiming())
	{
		SetTPCMotionMatchingType(CurrentMotionMatchingType == ETPCMotionMatchingType::With_OrientRotationToMovement ? ETPCMotionMatchingType::With_ControllerDesiredRotation : ETPCMotionMatchingType::With_OrientRotationToMovement);
	}
}

void ATPCharacter::ToggleCameraType()
{
	CameraHandler->ToggleCameraType();
}

void ATPCharacter::SetTPCMovementMode(ETPCPlayerMovementMode NewMovementMode)
{
	if (NewMovementMode == ETPCPlayerMovementMode::Walk)
	{
		GetCharacterMovement()->MaxWalkSpeed = MovementSettings.WalkSpeed;
		CurrentMovementMode = NewMovementMode;
	}

	if (NewMovementMode == ETPCPlayerMovementMode::Jog)
	{
		GetCharacterMovement()->MaxWalkSpeed = MovementSettings.JogSpeed;
		CurrentMovementMode = NewMovementMode;
		bIsTPCCrouched = false;
	}

	if (NewMovementMode == ETPCPlayerMovementMode::Sprint)
	{
		GetCharacterMovement()->MaxWalkSpeed = MovementSettings.SprintSpeed;
		CurrentMovementMode = NewMovementMode;
		bIsTPCCrouched = false;
	}

	if (NewMovementMode == ETPCPlayerMovementMode::Crouch)
	{
		if (bIsTPCCrouched)
		{
			bIsTPCCrouched = false;
			SetTPCMovementMode(ETPCPlayerMovementMode::Walk);
		}
		else
		{
			bIsTPCCrouched = true;
			GetCharacterMovement()->MaxWalkSpeed = MovementSettings.CrouchSpeed;
			CurrentMovementMode = NewMovementMode;
		}
	}

	CameraHandler->SetCrouchedCameraMode(bIsTPCCrouched);
}

void ATPCharacter::SetTPCAnimationState(ETPCAnimationState NewAnimationState)
{
	PlayerCurrentAnimationState = NewAnimationState;
}

void ATPCharacter::SetTPCMotionMatchingType(ETPCMotionMatchingType NewMotionMatchingType)
{
	if (NewMotionMatchingType == ETPCMotionMatchingType::With_ControllerDesiredRotation)
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		CurrentMotionMatchingType = NewMotionMatchingType;
	}

	if (NewMotionMatchingType == ETPCMotionMatchingType::With_OrientRotationToMovement)
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
		CurrentMotionMatchingType = NewMotionMatchingType;
	}
}

void ATPCharacter::PlayAnimationMontage(UAnimMontage* MontageToPlay)
{
	if (!GetMesh() || !MontageToPlay)
		return;

	auto* AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance)
		return;

	AnimInstance->Montage_Play(MontageToPlay);
}

void ATPCharacter::StartAiming()
{
	bIsAiming = true;
	CameraHandler->SetAimCameraMode(true);
	SetTPCMotionMatchingType(ETPCMotionMatchingType::With_ControllerDesiredRotation);
	CurrentlyEquippedWeaponType = GetCurrentlyEquippedWeaponTypeFromInv();
	if (GetHasWeaponInHand() && InventoryComponent)
	{
		if (InventoryComponent->GetCurrentlyEquippedWeaponType() == EWeaponType::Rifle)
		{
			InventoryComponent->ChangeWeaponSocket("WeaponAimSocketRifle");
		}
		if (InventoryComponent->GetCurrentlyEquippedWeaponType() == EWeaponType::Pistol)
		{
			InventoryComponent->ChangeWeaponSocket("WeaponAimSocketPistol");
		}
	}
}

void ATPCharacter::StopAiming()
{
	bIsAiming = false;
	CameraHandler->SetAimCameraMode(false);
	SetTPCMotionMatchingType(ETPCMotionMatchingType::With_OrientRotationToMovement);
	if (GetHasWeaponInHand() && InventoryComponent)
	{
		if (InventoryComponent->GetCurrentlyEquippedWeaponType() == EWeaponType::Rifle)
		{
			InventoryComponent->ChangeWeaponSocket("WeaponEquippedSocketRifle");
		}

		if (InventoryComponent->GetCurrentlyEquippedWeaponType() == EWeaponType::Pistol)
		{
			InventoryComponent->ChangeWeaponSocket("WeaponEquippedSocketPistol");
		}
	}
}

bool ATPCharacter::GetHasWeaponInHand()
{
	return InventoryComponent->HasWeaponEquipped();
}

bool ATPCharacter::GetIsAiming()
{
	return bIsAiming;
}

EWeaponType ATPCharacter::GetCurrentlyEquippedWeaponTypeFromInv()
{
	if (InventoryComponent)
	{
		return InventoryComponent->GetCurrentlyEquippedWeaponType();
	}

	return EWeaponType::None;
}

void ATPCharacter::DoAttack()
{
	if (InventoryComponent && GetIsAiming())
	{
		InventoryComponent->AttackWithCurrentWeapon(GetAimHitLocation());
	}
}

void ATPCharacter::DoReload()
{
	if (InventoryComponent && GetHasWeaponInHand())
	{
		InventoryComponent->ReloadCurrentlyEquippedWeapon();
	}
}

const FVector ATPCharacter::GetAimHitLocation()
{
	if (!PlayerCamera)
		return {0,0,0};
	
	FVector LineTraceStart = PlayerCamera->GetComponentLocation();  
	FVector LineTraceEnd = PlayerCamera->GetComponentLocation() + PlayerCamera->GetForwardVector() * 50000;  

	FHitResult HitResult;
	const TArray<AActor*> HitActors;
	
	UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		LineTraceStart,
		LineTraceEnd,
		TraceTypeQuery1,
		true,
		HitActors,
		EDrawDebugTrace::None,
		HitResult,
		true
		);

	if (HitResult.bBlockingHit)
	{
		return HitResult.ImpactPoint;
	}

	return LineTraceEnd;
}
