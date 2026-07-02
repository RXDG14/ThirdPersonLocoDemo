#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class THIRDPERSONLOCODEMO_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ABullet();
	virtual void Tick(float DeltaTime) override;
	void SetBulletDirection(FRotator Direction);
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Bullet")
	UStaticMeshComponent* BulletMesh;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullet", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileComponent;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullet", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereComponent;
	
	UFUNCTION()
	void OnBulletSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
