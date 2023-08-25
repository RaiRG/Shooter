// Shooter Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "SPatrolEnvQueryContext.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SHOOTER_API USPatrolEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()

public:
    virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
};
