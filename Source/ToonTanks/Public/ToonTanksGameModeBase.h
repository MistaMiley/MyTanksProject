// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	//AToonTanksGameModeBase();
	void ActorDied(AActor* deadActor);
	APlayerController* GetTankPlayerController() const
	{
		return TankPlayerControllerRef;
	}
private:
	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController;
	APlayerController* TankPlayerControllerRef = nullptr;
protected:
	virtual void BeginPlay()override;
};
