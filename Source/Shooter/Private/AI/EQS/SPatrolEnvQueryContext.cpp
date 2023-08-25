// Shooter Game, All Rights Reserved.


#include "AI/EQS/SPatrolEnvQueryContext.h"

#include "SAICharacter.h"
#include "SAIController.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Point.h"


void USPatrolEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
    const auto QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());

    const auto Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner);
    if (!Blackboard) return;
    const auto Controller = Cast<ASAIController>(UAIBlueprintHelperLibrary::GetAIController(QueryOwner));
    if (!Controller) return;
    const auto Pawn = Cast<ASAICharacter>(Controller->GetPawn());
    if (!Pawn) return;    
    const auto ContextLocation = Pawn->GetStartLocation();
    UEnvQueryItemType_Point::SetContextHelper(ContextData, ContextLocation);
}
