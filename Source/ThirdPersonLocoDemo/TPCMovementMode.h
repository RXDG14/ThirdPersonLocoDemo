#pragma once

UENUM(BlueprintType)
enum class ETPCMovementMode : uint8
{
	Walk      UMETA(DisplayName = "Walk"),
	Jog       UMETA(DisplayName = "Jog"),
	Sprint   UMETA(DisplayName = "Sprint"),
	Crouch   UMETA(DisplayName = "Crouch")
};