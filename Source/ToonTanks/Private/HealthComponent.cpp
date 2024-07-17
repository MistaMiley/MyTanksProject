// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
//IMPLEMENT CONSTRUCTOR
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Health = MaxHealth;
	Super::BeginPlay();


	//add our functions  DamageTaken to owners OnTake Any Damage Event!
		
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	// ...
	
}



void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	if (Damage <= 0.f)
	{
		return;
	}
		Health -= Damage;
		UE_LOG(LogTemp, Warning, TEXT("Health= %f"), Health);

	
	UE_LOG(LogTemp, Warning, (TEXT("in OnDamageTaken() from OnTakeAnyDamage callback")));
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

