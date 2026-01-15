#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"

#include "MyCharacter.generated.h"

UCLASS()
class MINI3DRPG_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	// UI class
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> JumpHintWidgetClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> WalkHintWidgetClass;

		// UI instance
	UPROPERTY()
	UUserWidget* JumpHintWidget;

	UPROPERTY()
	UUserWidget* WalkHintWidget;

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowJumpHint();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void HideJumpHint();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowWalkHint();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void HideWalkHint();
};
