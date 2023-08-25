// Shooter Game, All Rights Reserved.


#include "AI/SAIController.h"

#include "BrainComponent.h"
#include "SAICharacter.h"
#include "SAIPerceptionComponent.h"

ASAIController::ASAIController()
{
    AIPerceptionComponent = CreateDefaultSubobject<USAIPerceptionComponent>("AIPerceptionComponent");
    SetPerceptionComponent(*AIPerceptionComponent);
}

void ASAIController::LaunchBehaviorTree()
{
    const auto AICharacter = Cast<ASAICharacter>(GetPawn());

    if (AICharacter)
    {
        RunBehaviorTree(AICharacter->BehaviorTreeAsset);
    }
}

void ASAIController::StopBehaviorTree()
{
    if (!BrainComponent) return;
    BrainComponent->StopLogic();
}
