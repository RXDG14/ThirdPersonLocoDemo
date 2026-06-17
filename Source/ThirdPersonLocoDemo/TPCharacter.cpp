#include "TPCharacter.h"

#include "CharacterTrajectoryComponent.h" 
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InventoryComponent.h"
#include "TPCPlayerEnums.h"
#include "GameFramework/CharacterMovementComponent.h"

ATPCharacter::ATPCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCharacterMovement()->MaxAcceleration = 1200.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1200.f;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 180.0f, 0.0f);

	bUseControllerRotationYaw = false;
	
	TrajectoryComponent = CreateDefaultSubobject<UCharacterTrajectoryComponent>(TEXT("CharacterTrajectoryComponent"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->bUsePawnControlRotation = true;
	
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	PlayerCamera->SetupAttachment(SpringArm);

	BackPackMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackPack"));
	BackPackMesh->SetupAttachment(GetMesh(), TEXT("BagpackSocket"));
}

void ATPCharacter::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("%s"),GetMesh()->DoesSocketExist(TEXT("BagpackSocket")) ? TEXT("YES") : TEXT("NO"));
	
	SetTPCMovementMode(ETPCPlayerEnums::Walk);
	SetTPCMotionMatchingType(ETPCMotionMatchingType::With_OrientRotationToMovement);
	SetTPCCameraType(ETPCCameraType::Far);
}

void ATPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateCameraPosition(DeltaTime);

	//InventoryComponent->equi
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
		EIC->BindAction(IA_MMTypeSwitch, ETriggerEvent::Started, this, &ATPCharacter::ToggleMotionMatchingType);
		EIC->BindAction(IA_CameraTypeSwitch, ETriggerEvent::Started, this, &ATPCharacter::ToggleCameraType);
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

	AddControllerPitchInput(LookAxisVector.Y * MovementSettings.LookSpeed);
	AddControllerYawInput(LookAxisVector.X * MovementSettings.LookSpeed);
}

void ATPCharacter::StartSprinting()
{
	SetTPCMovementMode(ETPCPlayerEnums::Sprint);
}

void ATPCharacter::StopSprinting()
{
	SetTPCMovementMode(ETPCPlayerEnums::Jog);
}

void ATPCharacter::ToggleCrouch()
{
	SetTPCMovementMode(ETPCPlayerEnums::Crouch);
}

void ATPCharacter::ToggleWalkJog()
{
	SetTPCMovementMode(CurrentMovementMode == ETPCPlayerEnums::Walk ? ETPCPlayerEnums::Jog : ETPCPlayerEnums::Walk);
}

void ATPCharacter::ToggleMotionMatchingType()
{
	SetTPCMotionMatchingType(CurrentMotionMatchingType == ETPCMotionMatchingType::With_OrientRotationToMovement ? ETPCMotionMatchingType::With_ControllerDesiredRotation : ETPCMotionMatchingType::With_OrientRotationToMovement);
}

void ATPCharacter::ToggleCameraType()
{
	switch (CurrentCameraType)
	{
	case ETPCCameraType::Close:
		SetTPCCameraType(ETPCCameraType::Far);
		break;

	case ETPCCameraType::Far:
		SetTPCCameraType(ETPCCameraType::VeryFar);
		break;

	case ETPCCameraType::VeryFar:
		SetTPCCameraType(ETPCCameraType::Far_Middle);
		break;

	case ETPCCameraType::Far_Middle:
	default:
		SetTPCCameraType(ETPCCameraType::Close);
		break;
	}
}

void ATPCharacter::SetTPCMovementMode(ETPCPlayerEnums NewMovementMode)
{
	if (NewMovementMode == ETPCPlayerEnums::Walk)
	{
		GetCharacterMovement()->MaxWalkSpeed = MovementSettings.WalkSpeed;
		CurrentMovementMode = NewMovementMode;
	}

	if (NewMovementMode == ETPCPlayerEnums::Jog)
	{
		GetCharacterMovement()->MaxWalkSpeed = MovementSettings.JogSpeed;
		CurrentMovementMode = NewMovementMode;
		bIsTPCCrouched = false;
	}

	if (NewMovementMode == ETPCPlayerEnums::Sprint)
	{
		GetCharacterMovement()->MaxWalkSpeed = MovementSettings.SprintSpeed;
		CurrentMovementMode = NewMovementMode;
		bIsTPCCrouched = false;
	}

	if (NewMovementMode == ETPCPlayerEnums::Crouch)
	{
		if (bIsTPCCrouched)
		{
			bIsTPCCrouched = false;
			SetTPCMovementMode(ETPCPlayerEnums::Walk);
		}
		else
		{
			bIsTPCCrouched = true;
			GetCharacterMovement()->MaxWalkSpeed = MovementSettings.CrouchSpeed;
			CurrentMovementMode = NewMovementMode;
		}
	}
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

void ATPCharacter::SetTPCCameraType(ETPCCameraType NewCameraType)
{
	CurrentCameraType = NewCameraType;

	switch (NewCameraType)
	{
	case ETPCCameraType::Close:
		DesiredCameraArmLength = CloseCamera.ArmLength;
		DesiredSocketOffset = CloseCamera.SocketOffset;
		break;

	case ETPCCameraType::Far:
		DesiredCameraArmLength = FarCamera.ArmLength;
		DesiredSocketOffset = FarCamera.SocketOffset;
		break;

	case ETPCCameraType::VeryFar:
		DesiredCameraArmLength = VeryFarCamera.ArmLength;
		DesiredSocketOffset = VeryFarCamera.SocketOffset;
		break;
		
	case ETPCCameraType::Far_Middle:
		DesiredCameraArmLength = FarMiddleCamera.ArmLength;
		DesiredSocketOffset = FarMiddleCamera.SocketOffset;
		break;
	
	default:
		break;
	}
}

void ATPCharacter::UpdateCameraPosition(float DeltaTime)
{
	if (bIsTPCCrouched)
	{
		DesiredSocketOffset.Z = 0;
	}
	else
	{
		DesiredSocketOffset.Z = 50;
	}
	
	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, DesiredCameraArmLength, DeltaTime, CameraInterpSpeed);
	SpringArm->SocketOffset = FMath::VInterpTo(SpringArm->SocketOffset, DesiredSocketOffset, DeltaTime, CameraInterpSpeed);
}
