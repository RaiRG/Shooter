// Shooter Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/SBaseWeapon.h"
#include "SRifleWeapon.generated.h"

class USoundCue;
/**
 * 
 */
UCLASS()
class SHOOTER_API ASRifleWeapon : public ASBaseWeapon
{
	GENERATED_BODY()

    virtual void Fire() override;
    virtual void StopFire() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* FireSound;

private:
    UPROPERTY()
    UAudioComponent* FireAudioComponent;

    void SetSoundActive(bool bIsActive);
    void InitAudio();
};
