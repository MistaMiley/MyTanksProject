// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include"Kismet/GameplayStatics.h"
#include "tank.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime)override;

	//moved begin play out of protected
//protected:
	virtual void BeginPlay() override;

	private:

		class ATank *PlayerTank;
	
	UPROPERTY(Category = "TargettingProperties", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float TargetRange = 200.0f;
	bool bTargetInRange = false;
	float FireRate = 1.f;
	FTimerHandle FireRateTimerHandle;
	void CheckFireCondition();
};
