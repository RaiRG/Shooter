// Shooter Game, All Rights Reserved.


#include "AI/SAIController.h"

#include "BrainComponent.h"
#include "SAICharacter.h"
#include "SAIPerceptionComponent.h"

ASAIController::ASAIController()
{
    AIPerceptionComponent = CreateDefaultSubobject<USAIPerceptionComponent>("AIPerceptionComponent");
    SetPerceptionComponent(*AIPerceptionComponent);

    bWantsPlayerState = true;
}

void ASAIController::LaunchBehaviorTree()
{
    if (!BrainComponent || !BrainComponent->IsRunning())
    {
        const auto AICharacter = Cast<ASAICharacter>(GetPawn());
        if (AICharacter)
        {
            RunBehaviorTree(AICharacter->BehaviorTreeAsset);
        }
    }
    else
    {
        BrainComponent->StartLogic();
    }
}

void ASAIController::StopBehaviorTree()
{
    if (!BrainComponent) return;
    BrainComponent->StopLogic("Need");
}
