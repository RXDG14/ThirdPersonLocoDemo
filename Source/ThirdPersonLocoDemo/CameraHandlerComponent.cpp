#include "CameraHandlerComponent.h"
#include "GameFramework/SpringArmComponent.h"

UCameraHandlerComponent::UCameraHandlerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCameraHandlerComponent::InitializeCamera(USpringArmComponent* InSpringArm)
{
	SpringArmRef = InSpringArm;
	
	SetCameraType(CurrentCameraType);
}

void UCameraHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateCameraPosition(DeltaTime);
}

void UCameraHandlerComponent::SetCameraType(ETPCCameraType NewCameraType)
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

void UCameraHandlerComponent::ToggleCameraType()
{
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

void UCameraHandlerComponent::SetCrouched(bool bNewCrouched)
{
	bIsTpcCrouched = bNewCrouched;
}

void UCameraHandlerComponent::UpdateCameraPosition(float DeltaTime)
{
	if (!SpringArmRef)
	{
		return;
	}

	DesiredSocketOffset.Z = bIsTpcCrouched ? 0.f : 50.f;

	SpringArmRef->TargetArmLength = FMath::FInterpTo(SpringArmRef->TargetArmLength, DesiredCameraArmLength, DeltaTime, CameraInterpSpeed);
	SpringArmRef->SocketOffset = FMath::VInterpTo(SpringArmRef->SocketOffset, DesiredSocketOffset, DeltaTime, CameraInterpSpeed);
}