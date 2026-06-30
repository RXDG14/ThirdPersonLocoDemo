#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ThirdPersonLocoDemo/Enums/TPCWeaponEnums.h"
#include "TPCharacter.generated.h"

enum class ETPCAnimationState : uint8;
enum class ETPCPlayerMovementMode : uint8;
enum class ETPCMotionMatchingType : uint8;
struct FInputActionValue;

USTRUCT(BlueprintType)
struct FTPCMovementSettings
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	float WalkSpeed = 200;

	UPROPERTY(EditDefaultsOnly)
	float CrouchSpeed = 250;

	UPROPERTY(EditDefaultsOnly)
	float JogSpeed = 450;

	UPROPERTY(EditDefaultsOnly)
	float SprintSpeed = 600;

	UPROPERTY(EditDefaultsOnly)
	float LookSpeed = 0.3f;

	UPROPERTY(EditDefaultsOnly)
	float LookSpeedAiming = 0.15f; // slower is better for mouse look
};

UCLASS()
class THIRDPERSONLOCODEMO_API ATPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATPCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void SetTPCAnimationState(ETPCAnimationState NewAnimationState);
	
protected:
	virtual void BeginPlay() override;
	
private:
	// Input____________________________________________________________
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
	class UInputAction* IA_Interact;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UInputAction* IA_MMTypeSwitch;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UInputAction* IA_CameraTypeSwitch;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UInputAction* IA_Drop;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UInputAction* IA_Holster;


	// Attachments____________________________________________________________
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* PlayerCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BackPackMesh;


	// Actor Components____________________________________________________________
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraHandlerComponent* CameraHandler;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory", meta=(AllowPrivateAccess="true"))
	class UInventoryComponent* InventoryComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UInteractionComponent* InteractionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCharacterTrajectoryComponent* TrajectoryComponent;

	
	// Animations____________________________________________________________
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attributes_Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AM_Pickup;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attributes_Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AM_Holster;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Attributes_Movement", meta = (AllowPrivateAccess = "true"))
	ETPCAnimationState PlayerCurrentAnimationState;
	
	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void Notify_OnWeaponHolstered();
	
	// Weapons____________________________________________________________
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Attributes_Weapon", meta = (AllowPrivateAccess = "true"))
	bool bIsAiming = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Attributes_Weapon", meta = (AllowPrivateAccess = "true"))
	EWeaponType CurrentlyEquippedWeaponType;

	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	bool GetHasWeaponInHand();
	
	// Attributes_Movement____________________________________________________________
	UPROPERTY(EditDefaultsOnly, Category="Attributes_Movement")
	FTPCMovementSettings MovementSettings;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Attributes_Movement", meta = (AllowPrivateAccess = "true"))
	bool bIsTPCCrouched = false;


	ETPCPlayerMovementMode CurrentMovementMode;
	ETPCMotionMatchingType CurrentMotionMatchingType;
	////////////////////////////////////////////////////////////////////////////////
	
	void MovePlayer(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);
	void DropWeapon(const FInputActionValue& Value);
	void HolsterWeapon(const FInputActionValue& Value);
	void StartSprinting();
	void StopSprinting();
	void ToggleCrouch();
	void ToggleWalkJog();
	void ToggleMotionMatchingType();
	void ToggleCameraType();
	void SetTPCMovementMode(ETPCPlayerMovementMode NewMovementMode);
	void SetTPCMotionMatchingType(ETPCMotionMatchingType NewMotionMatchingType);
	void PlayAnimationMontage(UAnimMontage* MontageToPlay);
	void StartAiming();
	void StopAiming();
	bool GetIsAiming();
	EWeaponType GetCurrentlyEquippedWeaponTypeFromInv();
};