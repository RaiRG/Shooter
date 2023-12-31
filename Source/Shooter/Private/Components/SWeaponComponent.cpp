// Shooter Game, All Rights Reserved.


#include "Components/SWeaponComponent.h"
#include "SBaseWeapon.h"
#include "GameFramework/Character.h"


USWeaponComponent::USWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void USWeaponComponent::Fire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->Fire();
}

void USWeaponComponent::StopFire()
{
    if (!CurrentWeapon) return;
    CurrentWeapon->StopFire();
}

void USWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
}

void USWeaponComponent::SpawnWeapon()
{
	if (!GetWorld()) return;

	CurrentWeapon = GetWorld()->SpawnActor<ASBaseWeapon>(WeaponClass);
	if (!CurrentWeapon) return;

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return;
    
	FAttachmentTransformRules AttachmentRule(EAttachmentRule::SnapToTarget, false);
	CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRule, WeaponAttachSocketName);
	CurrentWeapon->SetOwner(Character);
}

