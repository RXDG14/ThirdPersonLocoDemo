#pragma once

UENUM(BlueprintType)
enum class ETPCPlayerEnums : uint8
{
	Walk      UMETA(DisplayName = "Walk"),
	Jog       UMETA(DisplayName = "Jog"),
	Sprint   UMETA(DisplayName = "Sprint"),
	Crouch   UMETA(DisplayName = "Crouch")
};


UENUM(BlueprintType)
enum class ETPCMotionMatchingType : uint8
{
	With_OrientRotationToMovement      UMETA(DisplayName = "With_OrientRotationToMovement"),
	With_ControllerDesiredRotation       UMETA(DisplayName = "With_ControllerDesiredRotation")
};


UENUM (BlueprintType)
enum class ETPCCameraType : uint8
{
	Close      UMETA(DisplayName = "Close"),
	Far       UMETA(DisplayName = "Far"),
	VeryFar   UMETA(DisplayName = "VeryFar"),
	Far_Middle   UMETA(DisplayName = "Far_Middle")
};