// Shooter Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SBaseCharacter.generated.h"


class UTextRenderComponent;
class USWeaponComponent;
class USHealthComponent;

UCLASS()
class SHOOTER_API ASBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ASBaseCharacter();
    UFUNCTION(BlueprintCallable, Category="Movement")
    float GetMovementDirection();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    UPROPERTY(EditDefaultsOnly, Category = "Components")
    USHealthComponent* HealthComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Components")
    UTextRenderComponent* HealthTextComponent;
    
    virtual void OnDeath();

private:
    void OnHealthChanged(float Health);

};
