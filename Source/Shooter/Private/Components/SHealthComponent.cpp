// Shooter Game, All Rights Reserved.


#include "Components/SHealthComponent.h"


DEFINE_LOG_CATEGORY_STATIC(LogSHelathComponent, All, All);

USHealthComponent::USHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}


void USHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(MaxHealth);
	if (AActor* ComponentOwner = GetOwner())
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USHealthComponent::OnTakeAnyDamage);
	}
}

void USHealthComponent::SetHealth(float NewHealth)
{
	const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	Health = NextHealth;
	OnHealthChanged.Broadcast(Health);
}


void USHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy,
	AActor* DamageCauser)
{
	UE_LOG(LogSHelathComponent, Display, TEXT("OnTakeAnyDamage"));
	if (Damage <= 0.0f || IsDead() || !GetWorld()) return;
	GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	SetHealth(Health - Damage);
	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	else if (AutoHeal && GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
	}
}

void USHealthComponent::HealUpdate()
{
	SetHealth(Health + HealModifier);
	if (FMath::IsNearlyEqual(Health , MaxHealth) && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
	}
}
