// Shooter Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SAIController.generated.h"

class USAIPerceptionComponent;
/**
 * 
 */
UCLASS()
class SHOOTER_API ASAIController : public AAIController
{
	GENERATED_BODY()

    ASAIController();
public:
    UFUNCTION(BlueprintCallable)
    void LaunchBehaviorTree();
    UFUNCTION(BlueprintCallable)
    void StopBehaviorTree();
protected:

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Components")
    USAIPerceptionComponent* AIPerceptionComponent;
};
