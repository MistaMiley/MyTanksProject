// Fill out your copyright notice in the Description page of Project Settings.
//having a poblrm with paths :(
//

#include "../Public/ToonTanksGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "../Tank.h"
#include "../Tower.h"
#include "ToonTanksPlayerController.h"
#include "Item.h"

void AToonTanksGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Cast<AActor>(Tank))
	{
		Tank->HandleDestruction();
		if (ToonTanksPlayerController)
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
	}
	else if (ATower* DestroyedTower = Cast < ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
	}

		if (ToonTanksPlayerController)
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
			//Tank->DisableInput(ToonTanksPlayerController);
		}
	
}

int32 AToonTanksGameModeBase::GetTotalNumberOfPickups()
{
	return AItem::GetInstanceCount();
}

void AToonTanksGameModeBase::BeginPlay()
{
	Super::BeginPlay();
		//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItem::StaticClass(), FoundItems);
			
		//TotalNumberOfPickups = FoundItems.Num();

		Tank =Cast<ATank>( UGameplayStatics::GetPlayerPawn(this, 0));
		ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
		
		
}
