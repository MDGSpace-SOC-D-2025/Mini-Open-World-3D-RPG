#include "Mini3DRPG/Components/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(MaxHealth);
}

void UHealthComponent::TakeDamage(int32 Damage)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0, MaxHealth);
	OnHealthUpdate.Broadcast();
	if (CurrentHealth == 0)
	{
		OnDeath.Broadcast();

	}
}

void UHealthComponent::AddHealth(int32 Health)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + Health, 0, MaxHealth);
	OnHealthUpdate.Broadcast();

}

void UHealthComponent::SetHealth(int32 Health)
{
	CurrentHealth = FMath::Clamp(CurrentHealth = Health, 0, MaxHealth);
	OnHealthUpdate.Broadcast();

}

