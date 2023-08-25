// Shooter Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/SBaseCharacter.h"
#include "SPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class SHOOTER_API ASPlayerCharacter : public ASBaseCharacter
{
	GENERATED_BODY()

    ASPlayerCharacter();
protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Inputs | IMC")
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Inputs | Actions")
    UInputAction* MoveAction;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Inputs | Actions")
    UInputAction* TurnAction;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Inputs | Actions")
    UInputAction* FireAction;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(EditDefaultsOnly, Category="Components")
    USWeaponComponent* WeaponComponent;
    
private:
    void Move(const FInputActionValue& Value);
    void Turn(const FInputActionValue& Value);
};
