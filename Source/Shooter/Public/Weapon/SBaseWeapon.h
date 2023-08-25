// Shooter Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBaseWeapon.generated.h"

UCLASS()
class SHOOTER_API ASBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASBaseWeapon();

	virtual void Fire();
    virtual void StopFire();
protected:
	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditDefaultsOnly)
	FName MuzzleSocketName = "Muzzle";

	UPROPERTY(EditDefaultsOnly)
	float TraceMaxDistance = 1500.0f;
    
	UPROPERTY(EditDefaultsOnly)
	float DamageAmount = 10.0f;
    
	virtual void BeginPlay() override;
	void MakeShot();
	void MakeDamage(const FHitResult& HitResult);
	APlayerController* GetPlayerController() const;
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	FVector GetMuzzleWorldLocation() const;
	bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

};
