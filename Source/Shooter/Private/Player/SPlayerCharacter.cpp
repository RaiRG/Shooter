// Shooter Game, All Rights Reserved.


#include "Player/SPlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SWeaponComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ASPlayerCharacter::ASPlayerCharacter()
{
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->SocketOffset = FVector(20.0f, 100.0f, 60.0f);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    WeaponComponent = CreateDefaultSubobject<USWeaponComponent>("WeaponComponent");
}

void ASPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

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
}

void ASPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    if (UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
    {
        PlayerEnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,
            &ASPlayerCharacter::Move);
        PlayerEnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this,
            &ASPlayerCharacter::Turn);
        PlayerEnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, WeaponComponent,
            &USWeaponComponent::Fire);
        PlayerEnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Canceled, WeaponComponent,
            &USWeaponComponent::StopFire);
        PlayerEnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, WeaponComponent,
          &USWeaponComponent::StopFire);
    }
}

void ASPlayerCharacter::Move(const FInputActionValue& Value)
{
    auto DirectionY = Value[1];
    auto DirectionX = Value[0];

    if (DirectionY != 0.0f)
    {
        AddMovementInput(GetActorForwardVector(), DirectionY);
        MakeNoise(1, this);

    }
    if (DirectionX != 0.0f)
    {
        AddMovementInput(GetActorRightVector(), DirectionX);
        MakeNoise(1, this);
    }
}

void ASPlayerCharacter::Turn(const FInputActionValue& Value)
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
