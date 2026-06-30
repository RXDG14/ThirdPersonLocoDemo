#include "CameraHandlerComponent.h"
#include "GameFramework/SpringArmComponent.h"

UCameraHandlerComponent::UCameraHandlerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCameraHandlerComponent::InitializeCamera(USpringArmComponent* InSpringArm, UCameraComponent* InCamera)
{
	SpringArmRef = InSpringArm;
	CameraRef = InCamera;
	
	SetCameraType(CurrentCameraType);
}

void UCameraHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateCameraPosition(DeltaTime);
}

void UCameraHandlerComponent::SetCameraType(ETPCCameraType NewCameraType)
{
	PreviousCameraType = CurrentCameraType;
	
	switch (NewCameraType)
	{
	case ETPCCameraType::Aim:
		DesiredCameraArmLength = AimCamera.ArmLength;
		DesiredSocketOffset = AimCamera.SocketOffset;
		break;
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

	CurrentCameraType = NewCameraType;
}

void UCameraHandlerComponent::ToggleCameraType()
{
	if (GetAimCameraMode())
		return;

	PreviousCameraType = CurrentCameraType;
	
	switch (CurrentCameraType)
	{
	case ETPCCameraType::Close:
		SetCameraType(ETPCCameraType::Far);
		break;

	case ETPCCameraType::Far:
		SetCameraType(ETPCCameraType::VeryFar);
		break;

	case ETPCCameraType::VeryFar:
		SetCameraType(ETPCCameraType::Far_Middle);
		break;

	case ETPCCameraType::Far_Middle:
	default:
		SetCameraType(ETPCCameraType::Close);
		break;
	}
}

void UCameraHandlerComponent::SetCrouchedCameraMode(bool bNewCrouched)
{
	bIsInCrouchedCameraMode = bNewCrouched;
}

void UCameraHandlerComponent::SetAimCameraMode(bool bNewAim)
{
	bIsInAimCameraMode = bNewAim;
	if (bNewAim)
	{
		SetCameraType(ETPCCameraType::Aim);
	}
	else
	{
		SetCameraType(PreviousCameraType);
	}
}

void UCameraHandlerComponent::UpdateCameraPosition(float DeltaTime)
{
	if (!SpringArmRef)
	{
		return;
	}

	if (bIsInCrouchedCameraMode)
	{
		if (bIsInAimCameraMode)
		{
			DesiredSocketOffset.Z = 30.f;
		}
		else
		{
			DesiredSocketOffset.Z = 0.f;
		}
	}
	else
	{
		DesiredSocketOffset.Z = 50.f;
	}

	SpringArmRef->TargetArmLength = FMath::FInterpTo(SpringArmRef->TargetArmLength, DesiredCameraArmLength, DeltaTime, CameraInterpSpeed);
	SpringArmRef->SocketOffset = FMath::VInterpTo(SpringArmRef->SocketOffset, DesiredSocketOffset, DeltaTime, CameraInterpSpeed);
}

bool UCameraHandlerComponent::GetAimCameraMode()
{
	return bIsInAimCameraMode;
}
