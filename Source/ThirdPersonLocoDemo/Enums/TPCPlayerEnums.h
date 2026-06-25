#pragma once

UENUM(BlueprintType)
enum class ETPCPlayerMovementMode : uint8
{
	Walk      UMETA(DisplayName = "Walk"),
	Jog       UMETA(DisplayName = "Jog"),
	Sprint    UMETA(DisplayName = "Sprint"),
	Crouch    UMETA(DisplayName = "Crouch")
};

UENUM(BlueprintType)
enum class ETPCMotionMatchingType : uint8
{
	With_OrientRotationToMovement        UMETA(DisplayName = "With_OrientRotationToMovement"),
	With_ControllerDesiredRotation       UMETA(DisplayName = "With_ControllerDesiredRotation")
};


UENUM (BlueprintType)
enum class ETPCCameraType : uint8
{
	Aim          UMETA(DisplayName = "Aim"),
	Close        UMETA(DisplayName = "Close"),
	Far          UMETA(DisplayName = "Far"),
	VeryFar      UMETA(DisplayName = "VeryFar"),
	Far_Middle   UMETA(DisplayName = "Far_Middle")
};

UENUM(BlueprintType)
enum class ETPCAnimationState : uint8
{
	Unarmed    UMETA(DisplayName = "Unarmed"),
	Pistol     UMETA(DisplayName = "Pistol"),
	Rifle      UMETA(DisplayName = "Rifle"),
	Melee      UMETA(DisplayName = "Melee")
};