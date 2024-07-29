// Fill out your copyright notice in the Description page of Project Settings.
//having a poblrm with paths :(
//

#include "../Public/ToonTanksGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "../Tank.h"
#include "../Tower.h"
#include "ToonTanksPlayerController.h"

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

void AToonTanksGameModeBase::BeginPlay()
{
	Super::BeginPlay();
		Tank =Cast<ATank>( UGameplayStatics::GetPlayerPawn(this, 0));
		ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
}
