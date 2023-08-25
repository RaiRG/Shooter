// Shooter Game, All Rights Reserved.


#include "AI/Tasks/SForgetWhereHaveSeenLastTimeTask.h"

#include "BehaviorTree/BlackboardComponent.h"

USForgetWhereHaveSeenLastTimeTask::USForgetWhereHaveSeenLastTimeTask()
{
    NodeName = "Forget Last Position For Reaching Enemy";
}

EBTNodeResult::Type USForgetWhereHaveSeenLastTimeTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Controller || !Blackboard) return EBTNodeResult::Failed;
    
    Blackboard->ClearValue(LastPositionKey.SelectedKeyName);
    return EBTNodeResult::Succeeded;
}
