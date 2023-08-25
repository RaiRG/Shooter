// Shooter Game, All Rights Reserved.


#include "Components/SAIPerceptionComponent.h"

#include "AIController.h"
#include "SHealthComponent.h"
#include "Perception/AISense_Damage.h"

DEFINE_LOG_CATEGORY_STATIC(LogSAIPerceptionComponent, All, All);
AActor* USAIPerceptionComponent::GetClosestEnemy(TSubclassOf<UAISense> SenseForSearching) const
{
    TArray<AActor*> PercieveActors;
    GetCurrentlyPerceivedActors(SenseForSearching, PercieveActors);
    auto Result =  GetClosestActor(PercieveActors);
    UE_LOG(LogSAIPerceptionComponent, Display, TEXT("%s found %s"), *SenseForSearching->GetName(), Result ? *Result->GetName() : *FString("Null"));
    return Result;
}

APawn* USAIPerceptionComponent::GetPawn() const
{
    const auto Controller = Cast<AAIController>(GetOwner());

    if (!Controller) return nullptr;
    const auto Pawn = Controller->GetPawn();
    if (!Pawn) return nullptr;
    return Pawn;
}

AActor* USAIPerceptionComponent::GetClosestActor(TArray<AActor*>& AllActors) const
{
    const auto Pawn = GetPawn();
    float BestDistance = MAX_FLT;
    AActor* BestActor = nullptr;
    for (const auto Actor : AllActors)
    {
        const auto HealthComponent = Actor->FindComponentByClass<USHealthComponent>();
        if (HealthComponent && !HealthComponent->IsDead())
        {
            const auto CurrentDistance = (Actor->GetActorLocation() - Pawn->GetActorLocation()).Size();
            if (CurrentDistance < BestDistance)
            {
                BestDistance = CurrentDistance;
                BestActor = Actor;
            }
        }
    }
    return BestActor;
}
