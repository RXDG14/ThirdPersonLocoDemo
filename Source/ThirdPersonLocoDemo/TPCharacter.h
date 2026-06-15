#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPCharacter.generated.h"

enum class ETPCCameraType : uint8;
enum class ETPCMotionMatchingType : uint8;
enum class ETPCPlayerEnums : uint8;
struct FInputActionValue;

USTRUCT(BlueprintType)
struct FTPCMovementSettings
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	float CrouchSpeed = 100;
	
	UPROPERTY(EditDefaultsOnly)
	float WalkSpeed = 200;

	UPROPERTY(EditDefaultsOnly)
	float JogSpeed = 450;

	UPROPERTY(EditDefaultsOnly)
	float SprintSpeed = 600;

	UPROPERTY(EditDefaultsOnly)
	float LookSpeed = 0.3f; // slower is better for mouse look
};

USTRUCT(BlueprintType)
struct FTPCCameraSettings
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	float ArmLength;

	UPROPERTY(EditDefaultsOnly)
	FVector SocketOffset;
};

UCLASS()
class THIRDPERSONLOCODEMO_API ATPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATPCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	virtual void BeginPlay() override;
	
private:

	// Input
	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UInputAction* IA_Move;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UInputAction* IA_Look;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UInputAction* IA_Jump;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UInputAction* IA_Sprint;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UInputAction* IA_Crouch;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UInputAction* IA_Walk;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UInputAction* IA_Aim;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UInputAction* IA_Attack;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UInputAction* IA_MMTypeSwitch;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UInputAction* IA_CameraTypeSwitch;


	// Attached Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* PlayerCamera;


	// Animation
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Animation", meta = (AllowPrivateAccess = "true"))
	class UCharacterTrajectoryComponent* TrajectoryComponent;

	
	// Weapons
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Attributes_Weapons", meta = (AllowPrivateAccess = "true"))
	bool bIsHoldingWeapon = false;

	// Aiming

	
	// Attributes_Movement
	UPROPERTY(EditDefaultsOnly, Category="Attributes_Movement")
	FTPCMovementSettings MovementSettings;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Attributes_Movement", meta = (AllowPrivateAccess = "true"))
	bool bIsTPCCrouched = false;

	// Attributes_Camera
	UPROPERTY(EditDefaultsOnly,Category="Attributes_Camera")
	FTPCCameraSettings CloseCamera;

	UPROPERTY(EditDefaultsOnly,Category="Attributes_Camera")
	FTPCCameraSettings FarCamera;

	UPROPERTY(EditDefaultsOnly,Category="Attributes_Camera")
	FTPCCameraSettings VeryFarCamera;

	UPROPERTY(EditDefaultsOnly,Category="Attributes_Camera")
	FTPCCameraSettings FarMiddleCamera;
	
	float CameraInterpSpeed = 3.0f; // value = how fast?
	float DesiredCameraArmLength = 0;
	FVector DesiredSocketOffset = {0,0,0};
	
	ETPCPlayerEnums CurrentMovementMode;
	ETPCMotionMatchingType CurrentMotionMatchingType;
	ETPCCameraType CurrentCameraType;
	
	void MovePlayer(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartSprinting();
	void StopSprinting();
	void ToggleCrouch();
	void ToggleWalkJog();
	void ToggleMotionMatchingType();
	void ToggleCameraType();
	void SetTPCMovementMode(ETPCPlayerEnums NewMovementMode);
	void SetTPCMotionMatchingType(ETPCMotionMatchingType NewMotionMatchingType);
	void SetTPCCameraType(ETPCCameraType NewCameraType);
	void UpdateCameraPosition(float DeltaTime);
};
