#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Enums/TPCPlayerEnums.h"
#include "CameraHandlerComponent.generated.h"

class UCameraComponent;
class USpringArmComponent;

USTRUCT(BlueprintType)
struct FTPCCameraSettings
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	float ArmLength = 100;

	UPROPERTY(EditDefaultsOnly)
	FVector SocketOffset = FVector(0, 50, 50);
};


UCLASS(ClassGroup=(Camera), meta=(BlueprintSpawnableComponent))
class THIRDPERSONLOCODEMO_API UCameraHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCameraHandlerComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void InitializeCamera(USpringArmComponent* InSpringArm, UCameraComponent* InCamera);
	
	void ToggleCameraType();
	void SetCrouchedCameraMode(bool bNewCrouched);
	void SetAimCameraMode(bool bNewAim);
	
	ETPCCameraType GetPreviousCameraType() const { return PreviousCameraType; }
private:
	UPROPERTY()
	USpringArmComponent* SpringArmRef = nullptr;

	UPROPERTY()
	UCameraComponent* CameraRef = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Camera_Presets")
	FTPCCameraSettings AimCamera = {50, {0,40,50}};

	UPROPERTY(EditDefaultsOnly, Category="Camera_Presets")
	FTPCCameraSettings CloseCamera = {100, {0,40,50}};

	UPROPERTY(EditDefaultsOnly, Category="Camera_Presets")
	FTPCCameraSettings FarCamera = {250, {0,50,50}};

	UPROPERTY(EditDefaultsOnly, Category="Camera_Presets")
	FTPCCameraSettings VeryFarCamera = {350, {0,50,50}};

	UPROPERTY(EditDefaultsOnly, Category="Camera_Presets")
	FTPCCameraSettings FarMiddleCamera = {300, {0,0,50}};

	UPROPERTY(EditDefaultsOnly, Category="Camera_Attributes")
	float CameraInterpSpeed = 3.0f; // higher = snappier

	ETPCCameraType PreviousCameraType;
	ETPCCameraType CurrentCameraType = ETPCCameraType::Far;
	FVector DesiredSocketOffset = FVector::ZeroVector;
	float DesiredCameraArmLength = 0.f;

	bool bIsInCrouchedCameraMode = false;
	bool bIsInAimCameraMode = false;

	void UpdateCameraPosition(float DeltaTime);
	ETPCCameraType GetCurrentCameraType() const { return CurrentCameraType; }
	void SetCameraType(ETPCCameraType NewCameraType);
	bool GetAimCameraMode();
};