// Shooter Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SHealthComponent.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API USHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USHealthComponent();

	FOnDeathSignature OnDeath;
	FOnHealthChangedSignature OnHealthChanged;

	float GetHealth() const { return Health; }
    
	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return FMath::IsNearlyZero(Health); }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Health", meta = (ClampMax=300.0f, ClampMin=1.0f))
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Heal")
	bool AutoHeal = true;

	UPROPERTY(EditDefaultsOnly, Category = "Heal", meta =(EditCondition=AutoHeal))
	float HealUpdateTime = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Heal", meta =(EditCondition=AutoHeal))
	float HealDelay = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Heal", meta =(EditCondition=AutoHeal))
	float HealModifier = 5.0f;

private:
	float Health;
	void SetHealth(float NewHealth);

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy,
		AActor* DamageCauser);

	FTimerHandle HealTimerHandle;
	void HealUpdate();

};
