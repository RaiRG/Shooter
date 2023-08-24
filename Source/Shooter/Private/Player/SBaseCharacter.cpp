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

DEFINE_LOG_CATEGORY_STATIC(LogSBaseCharcter, All, All);

ASBaseCharacter::ASBaseCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->SocketOffset = FVector(20.0f, 100.0f, 60.0f);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    HealthComponent = CreateDefaultSubobject<USHealthComponent>("HealthComponent");
    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
    HealthTextComponent->SetupAttachment(GetRootComponent());
    HealthTextComponent->SetIsReplicated(true);

    WeaponComponent = CreateDefaultSubobject<USWeaponComponent>("WeaponComponent");
}


void ASBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthComponent);
    check(HealthTextComponent)
    check(GetCharacterMovement());
    check(GetMesh());
    check(WeaponComponent);

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
            PC->GetLocalPlayer()))
        {
            Subsystem->ClearAllMappings();
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }

    HealthComponent->OnDeath.AddUObject(this, &ASBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ASBaseCharacter::OnHealthChanged);
}

void ASBaseCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), HealthComponent->GetHealth())));
}

void ASBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    UE_LOG(LogSBaseCharcter, Display, TEXT("SetupPlayerInputComponent %i"), HasAuthority());
    if (UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
    {
        PlayerEnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,
            &ASBaseCharacter::Move);
        PlayerEnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this,
            &ASBaseCharacter::Turn);
        PlayerEnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, WeaponComponent,
            &USWeaponComponent::Fire);
    }
}

void ASBaseCharacter::Move(const FInputActionValue& Value)
{
    auto DirectionY = Value[1];
    auto DirectionX = Value[0];

    if (DirectionY != 0.0f)
    {
        AddMovementInput(GetActorForwardVector(), DirectionY);
    }
    if (DirectionX != 0.0f)
    {
        AddMovementInput(GetActorRightVector(), DirectionX);
    }
}

void ASBaseCharacter::Turn(const FInputActionValue& Value)
{
    auto Direction = Value.Get<FVector2D>();

    if (Direction.Y != 0.0f)
    {
        AddControllerPitchInput(-1 * Direction.Y);
    }
    if (Direction.X != 0.0f)
    {
        AddControllerYawInput(Direction.X);
    }
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

