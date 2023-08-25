// Shooter Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "SAIPerceptionComponent.generated.h"

class ASBaseCharacter;
/**
 * 
 */
UCLASS()
class SHOOTER_API USAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
    AActor* GetClosestEnemy(TSubclassOf<UAISense> SenseForSearching) const;
    
private:
    APawn* GetPawn() const;
    AActor* GetClosestEnemy(TArray<AActor*>& AllActors) const;
    
};
