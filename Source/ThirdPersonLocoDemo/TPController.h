#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TPController.generated.h"

UCLASS()
class THIRDPERSONLOCODEMO_API ATPController : public APlayerController
{
	GENERATED_BODY()
public:

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	// Input
	UPROPERTY(EditDefaultsOnly, Category="Input")
	class UInputMappingContext* IMC_TPCharacter;
	
};
