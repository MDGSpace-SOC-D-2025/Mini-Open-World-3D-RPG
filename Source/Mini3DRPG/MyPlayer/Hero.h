#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"

#include "Hero.generated.h"

UCLASS()
class MINI3DRPG_API AHero : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

protected:

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* SprintAction;

public:
	// Sets default values for this character's properties
	AHero();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	//movement
	void Move(const FInputActionValue& InputValue);
	void Look(const FInputActionValue& InputValue);
	void Jump();

	//Sprinting
	void StartSprint();
	void StopSprint();

	UPROPERTY(EditAnywhere, Category = "Movement")
	float RunSpeed = 1000;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float WalkSpeed = 600;

	bool bIsRunning;

	//Stamina
	void UpdateStamina();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float MaxStamina;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float CurrentStamina;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float StaminaDrainTime;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float StaminaRefillTime;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float DelayBeforeRefill;

	float CurrentRefillDelayTime;

	bool bHasStamina;


};
