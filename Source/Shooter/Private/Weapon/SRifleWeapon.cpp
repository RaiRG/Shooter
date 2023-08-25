// Shooter Game, All Rights Reserved.


#include "Weapon/SRifleWeapon.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void ASRifleWeapon::Fire()
{
    Super::Fire();
    InitAudio();
}

void ASRifleWeapon::StopFire()
{
    SetSoundActive(false);
    Super::StopFire();
}

void ASRifleWeapon::SetSoundActive(bool bIsActive)
{
    if (FireAudioComponent)
    {
        FireAudioComponent->SetPaused(!bIsActive);
    }
}

void ASRifleWeapon::InitAudio()
{
    if (!FireAudioComponent)
    {
        FireAudioComponent = UGameplayStatics::SpawnSoundAttached(FireSound, SkeletalMeshComponent, MuzzleSocketName);
    }
    SetSoundActive(true);
}
