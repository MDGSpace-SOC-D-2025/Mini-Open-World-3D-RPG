#include "Mini3DRPG/MyPlayer/Hero.h"

#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AHero::AHero()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void AHero::BeginPlay()
{
	Super::BeginPlay();
	
	// Add Input mapping context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			//Add input context
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}
}

// Called every frame
void AHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateStamina();
}

// Called to bind functionality to input
void AHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHero::Move);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHero::Look);
		Input->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AHero::Jump);
		Input->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AHero::StartSprint);
		Input->BindAction(SprintAction, ETriggerEvent::Completed, this, &AHero::StopSprint);

	}

}

void AHero::Move(const FInputActionValue& InputValue)
{
	FVector2D InputVector = InputValue.Get<FVector2D>();

	if (IsValid(Controller))
	{
		//Get Forward direction
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		//Add movement input
		AddMovementInput(ForwardDirection, InputVector.Y);
		AddMovementInput(RightDirection, InputVector.X);

		UE_LOG(LogTemp, Warning, TEXT("Move input: %s"), *InputVector.ToString());

	}
}

void AHero::Look(const FInputActionValue& InputValue)
{
	FVector2D InputVector = InputValue.Get<FVector2D>();

	if (IsValid(Controller))
	{
		AddControllerYawInput(InputVector.X);
		AddControllerPitchInput(InputVector.Y);
	}
}

void AHero::Jump()
{
	ACharacter::Jump();
}

void AHero::StartSprint()
{
	if (bHasStamina)
	{
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;

		if (GetVelocity().Size() >= 0.5)
		{
			bIsRunning = true;
		}
		else
		{
			bIsRunning = false;
		}
	}
}

void AHero::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	bIsRunning = false;

}

void AHero::UpdateStamina()
{
	//Drain Stamina

	if (bIsRunning)
	{
		CurrentStamina -= StaminaDrainTime;
		CurrentRefillDelayTime = DelayBeforeRefill;
	}

	if (!bIsRunning && CurrentStamina < MaxStamina)
	{
		CurrentRefillDelayTime--;
		if (CurrentRefillDelayTime <= 0)
		{
			CurrentStamina += StaminaRefillTime;
		}
	}

	if (CurrentStamina <= 0)
	{
		bHasStamina = false;
		StopSprint();
	}
	else
		bHasStamina = true;

	GEngine->AddOnScreenDebugMessage(1,0.f,FColor::Green,FString::Printf(TEXT("Stamina: %.2f | Delay: %.2f | Running: %d | HasStamina: %d"), CurrentStamina, CurrentRefillDelayTime, bIsRunning, bHasStamina));

}
