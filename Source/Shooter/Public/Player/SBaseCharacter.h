// Shooter Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SBaseCharacter.generated.h"


class UTextRenderComponent;
class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class USWeaponComponent;
class USHealthComponent;

UCLASS()
class SHOOTER_API ASBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASBaseCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
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

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UTextRenderComponent* HealthTextComponent;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	USWeaponComponent* WeaponComponent;

public:
	UFUNCTION(BlueprintCallable, Category="Movement")
	float GetMovementDirection();

private:
	void Move(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);

	void OnDeath();
	void OnHealthChanged(float Health);

};
