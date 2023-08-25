// Shooter Game, All Rights Reserved.


#include "AI/SAICharacter.h"

#include "BrainComponent.h"
#include "SAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ASAICharacter::ASAICharacter()
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = ASAIController::StaticClass();

    bUseControllerRotationYaw = true;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 100.0f, 0.0f);
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
    }
}

void ASAICharacter::BeginPlay()
{
    Super::BeginPlay();

    // Save start location in blackboard:
    auto AIController = Cast<AAIController>(GetController());
    if (AIController)
    {
        auto Blackboard = AIController->GetBlackboardComponent();
        if (Blackboard)
        {
            StartLocation = GetActorLocation();
        }
    }
}

void ASAICharacter::OnDeath()
{
    Super::OnDeath();
    auto AIController = Cast<AAIController>(GetController());
    if (AIController && AIController->BrainComponent)
    {
        AIController->BrainComponent->Cleanup();
    }
}
