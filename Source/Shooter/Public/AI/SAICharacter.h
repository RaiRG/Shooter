// Shooter Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/SBaseCharacter.h"
#include "SAICharacter.generated.h"

class UBehaviorTree;
/**
 * 
 */
UCLASS()
class SHOOTER_API ASAICharacter : public ASBaseCharacter
{
    GENERATED_BODY()

    ASAICharacter();

protected:
    virtual void BeginPlay() override;

    virtual void OnDeath() override;

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI")
    UBehaviorTree* BehaviorTreeAsset;
    FVector GetStartLocation() { return StartLocation; }

private:
    FVector StartLocation;
};
