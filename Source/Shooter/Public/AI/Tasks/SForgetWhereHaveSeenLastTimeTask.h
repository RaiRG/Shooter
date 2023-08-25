// Shooter Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SForgetWhereHaveSeenLastTimeTask.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API USForgetWhereHaveSeenLastTimeTask : public UBTTaskNode
{
	GENERATED_BODY()

    USForgetWhereHaveSeenLastTimeTask();
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    FBlackboardKeySelector LastPositionKey;

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
