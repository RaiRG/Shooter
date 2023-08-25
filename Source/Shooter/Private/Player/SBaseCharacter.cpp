// Shooter Game, All Rights Reserved.


#include "Player/SBaseCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SHealthComponent.h"
#include "SWeaponComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


ASBaseCharacter::ASBaseCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    HealthComponent = CreateDefaultSubobject<USHealthComponent>("HealthComponent");
    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
    HealthTextComponent->SetupAttachment(GetRootComponent());
    HealthTextComponent->SetIsReplicated(true);

}


void ASBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthComponent);
    check(HealthTextComponent)
    check(GetCharacterMovement());
    check(GetMesh());
    
    HealthComponent->OnDeath.AddUObject(this, &ASBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ASBaseCharacter::OnHealthChanged);
}

void ASBaseCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), HealthComponent->GetHealth())));
}


float ASBaseCharacter::GetMovementDirection()
{
    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto AngleBetweenForwardAndVelocity = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
    return FMath::RadiansToDegrees(AngleBetweenForwardAndVelocity) * FMath::Sign(CrossProduct.Z);
}

void ASBaseCharacter::OnDeath()
{
    GetMesh()->SetCollisionProfileName("Ragdoll");
    GetMesh()->SetSimulatePhysics(true);
    GetCharacterMovement()->DisableMovement();
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASBaseCharacter::OnHealthChanged(float Health)
{
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));

}

