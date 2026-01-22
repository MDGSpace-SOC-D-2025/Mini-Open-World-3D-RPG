#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthUpdate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MINI3DRPG_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	virtual void TakeDamage(int32 Damage);
	UFUNCTION(BlueprintCallable)
	virtual void AddHealth(int32 Health);
	UFUNCTION(BlueprintCallable)
	virtual void SetHealth(int32 Health);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 MaxHealth;

	UPROPERTY(BlueprintReadOnly)
	int32 CurrentHealth;
		
	UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeath;
	UPROPERTY(BlueprintAssignable)
	FOnHealthUpdate OnHealthUpdate;

};
