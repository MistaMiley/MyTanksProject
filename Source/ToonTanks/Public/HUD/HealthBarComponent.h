// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
//#include "HUD/HealthBarComponent.h"
#include "HUD/HealthBar.h"
#include "HealthBarComponent.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API UHealthBarComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:
	void Set_HealthBar_Percentage(float Percent);
	void Set_SpeedBar_Percentage(float Percent);
	void Set_RightTriggerBar_Percentage(float Percent);
	void Set_LeftTriggerBar_Percentage(float Percent);

private:

	UPROPERTY()
	UHealthBar	*SpeedBarWidget;
	UPROPERTY()
	UHealthBar	*LeftTriggerBarWidget;
	UPROPERTY()
	UHealthBar	*RightTriggerBarWidget;
	UPROPERTY()
	UHealthBar	*HealthBarWidget;
};
