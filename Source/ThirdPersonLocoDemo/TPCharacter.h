#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPCharacter.generated.h"

enum class ETPCMovementMode : uint8;
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

	
	// Attributes
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attributes", meta = (AllowPrivateAccess = "true"))
	float CrouchSpeed = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attributes", meta = (AllowPrivateAccess = "true"))
	float WalkSpeed = 200;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attributes", meta = (AllowPrivateAccess = "true"))
	float JogSpeed = 450;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attributes", meta = (AllowPrivateAccess = "true"))
	float SprintSpeed = 600;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Attributes", meta = (AllowPrivateAccess = "true"))
	bool bIsTPCCrouched = false;

	ETPCMovementMode CurrentMovementMode;
	void MovePlayer(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartSprinting();
	void StopSprinting();
	void ToggleCrouch();
	void ToggleWalkJog();
	void SetTPCMovementMode(ETPCMovementMode NewMovementMode);
	
};
