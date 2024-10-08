// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "HealthBar.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta =(BindWidget))
	class UProgressBar* SpeedBar;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar *LeftTriggerPowerBar;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar *RightTriggerPowerBar;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar*HealthBar;
	//UPROPERTY(meta = (BindWidget))
};
