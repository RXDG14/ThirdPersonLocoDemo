#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPCharacter.generated.h"

enum class ETPCCameraType : uint8;
enum class ETPCMotionMatchingType : uint8;
enum class ETPCPlayerEnums : uint8;
struct FInputActionValue;

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
	class UInputAction* IA_Shoot;

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
	

	// Aiming

	
	// Attributes_Movement
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attributes_Movement", meta = (AllowPrivateAccess = "true"))
	float CrouchSpeed = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attributes_Movement", meta = (AllowPrivateAccess = "true"))
	float WalkSpeed = 200;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attributes_Movement", meta = (AllowPrivateAccess = "true"))
	float JogSpeed = 450;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attributes_Movement", meta = (AllowPrivateAccess = "true"))
	float SprintSpeed = 600;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Attributes_Movement", meta = (AllowPrivateAccess = "true"))
	bool bIsTPCCrouched = false;

	// Attributes_Camera
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attributes_Camera", meta = (AllowPrivateAccess = "true"))
	float CameraArmLengthClose = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attributes_Camera", meta = (AllowPrivateAccess = "true"))
	FVector SocketOffsetClose = {0,50,50};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attributes_Camera", meta = (AllowPrivateAccess = "true"))
	float CameraArmLengthFar = 250;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attributes_Camera", meta = (AllowPrivateAccess = "true"))
	FVector SocketOffsetFar = {0,60,50};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attributes_Camera", meta = (AllowPrivateAccess = "true"))
	float CameraArmLengthVeryFar = 350;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attributes_Camera", meta = (AllowPrivateAccess = "true"))
	FVector SocketOffsetVeryFar = {0,60,50};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attributes_Camera", meta = (AllowPrivateAccess = "true"))
	float CameraArmLengthFarMiddle = 300;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attributes_Camera", meta = (AllowPrivateAccess = "true"))
	FVector SocketOffsetFarMiddle = {0,0,50};

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
