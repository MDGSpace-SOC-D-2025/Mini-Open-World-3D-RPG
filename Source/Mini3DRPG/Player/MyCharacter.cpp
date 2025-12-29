// Fill out your copyright notice in the Description page of Project Settings.


#include "Mini3DRPG/Player/MyCharacter.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyCharacter::ShowJumpHint()
{
	if (!JumpHintWidget && JumpHintWidgetClass)
	{
		JumpHintWidget = CreateWidget<UUserWidget>(
			GetWorld(),
			JumpHintWidgetClass
		);

		if (JumpHintWidget)
		{
			JumpHintWidget->AddToViewport();
		}
	}
}

void AMyCharacter::HideJumpHint()
{
	if (JumpHintWidget)
	{
		JumpHintWidget->RemoveFromParent();
		JumpHintWidget = nullptr;
	}
}

void AMyCharacter::ShowWalkHint()
{
	if (!WalkHintWidget && WalkHintWidgetClass)
	{
		WalkHintWidget = CreateWidget<UUserWidget>(
			GetWorld(),
			WalkHintWidgetClass
		);

		if (WalkHintWidget)
		{
			WalkHintWidget->AddToViewport();
		}
	}
}

void AMyCharacter::HideWalkHint()
{
	if (WalkHintWidget)
	{
		WalkHintWidget->RemoveFromParent();
		WalkHintWidget = nullptr;
	}
}
