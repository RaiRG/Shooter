// Shooter Game, All Rights Reserved.


#include "AI/Services/SFindEnemyForChaseService.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "SAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogSFindEnemyForChaseService, All, All);

USFindEnemyForChaseService::USFindEnemyForChaseService()
{
    NodeName = "Find Enemy For Chase";
}

void USFindEnemyForChaseService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    if (const auto Blackboard = OwnerComp.GetBlackboardComponent())
    {
        const auto Controller = OwnerComp.GetAIOwner();
        if (const auto PerceptionComponent = Controller->FindComponentByClass<USAIPerceptionComponent>())
        {
            for (const auto SenseAccuracy : SensesPriorityWithPinpointAccuracy)
            {
                if (const auto Enemy = PerceptionComponent->GetClosestEnemy(SenseAccuracy.Sense))
                {
                    FVector FoundLocation = Enemy->GetActorLocation();
                    Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, Enemy);
                    if (!FMath::IsNearlyEqual(SenseAccuracy.DistanceAccuracyOfFinding, 0.0f) && Controller->GetPawn())
                    {
                        FoundLocation = FindLocationWithAccuracy(Controller->GetPawn(), Enemy->GetActorLocation(),
                            SenseAccuracy.DistanceAccuracyOfFinding);
                        UE_LOG(LogSFindEnemyForChaseService, Display, TEXT("Recalculate for: %s, result: %s"), *SenseAccuracy.Sense->GetName(), *FoundLocation.ToString());

                    }
                    else
                    {
                        UE_LOG(LogSFindEnemyForChaseService, Display, TEXT("Don't recalculate for: %s, result: %s"), *SenseAccuracy.Sense->GetName(), *FoundLocation.ToString());

                    }
                    Blackboard->SetValueAsVector(FoundEnemyPosition.SelectedKeyName, FoundLocation);
                    return Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
                }
            }
        }
        Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, nullptr);
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

FVector USFindEnemyForChaseService::FindLocationWithAccuracy(APawn* Pawn, const FVector StartLocation, const float AccuracyDistance) const
{
    const auto NavSys = UNavigationSystemV1::GetCurrent(Pawn);
    FNavLocation NavLocation;
    const auto IsFound = NavSys->GetRandomReachablePointInRadius(StartLocation, AccuracyDistance, NavLocation);
    return IsFound ? NavLocation : StartLocation;
}
