// Shooter Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SFindEnemyForChaseService.generated.h"

class UAISense;

USTRUCT(BlueprintType)
struct FSenseAccuracy
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TSubclassOf<UAISense> Sense;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    float DistanceAccuracyOfFinding = 0.0f;
    
};
/**
 * Находит врага по указанным чувствам в порядке приоритета. Если враг найден, определяет, как точно может найти цель.
 */
UCLASS()
class SHOOTER_API USFindEnemyForChaseService : public UBTService
{
	GENERATED_BODY()

    USFindEnemyForChaseService();
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector FoundEnemyPosition;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta=(ToolTip=""))
    TArray<FSenseAccuracy> SensesPriorityWithPinpointAccuracy;

    
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
    
	FVector FindLocationWithAccuracy(APawn* Pawn, const FVector StartLocation, const float AccuracyRadius) const;
};
