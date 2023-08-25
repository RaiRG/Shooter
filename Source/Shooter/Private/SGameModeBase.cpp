// Shooter Game, All Rights Reserved.


#include "SGameModeBase.h"

#include "AIController.h"
#include "SPlayerState.h"
#include "UI/SHUD.h"

DEFINE_LOG_CATEGORY_STATIC(LogSGameModeBase, All, All);

ASGameModeBase::ASGameModeBase()
{
    HUDClass = ASHUD::StaticClass();
    PlayerStateClass = ASPlayerState::StaticClass();
}

void ASGameModeBase::StartPlay()
{
    Super::StartPlay();
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller) continue;

        const auto PlayerState = Cast<ASPlayerState>(Controller->PlayerState);
        if (!PlayerState) continue;

        const auto IsBot = Cast<AAIController>(Controller);
        PlayerState->SetTeamID(IsBot ? 1 : 0);
        UE_LOG(LogSGameModeBase, Display, TEXT("Set to %s ID %i"), *Controller->GetName(), IsBot ? 1 : 0);
    }
}
