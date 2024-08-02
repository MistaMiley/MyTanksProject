// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/HealthBarComponent.h"
#include "Components/WidgetComponent.h"
#include "HUD/HealthBar.h"

void UHealthBarComponent::Set_HealthBar_Percentage(float Percent)
{
	if (!HealthBarWidget)
	{
		HealthBarWidget = Cast<UHealthBar>(GetUserWidgetObject());
	}
	if (HealthBarWidget)
	{
		HealthBarWidget->HealthBar->SetPercent(Percent);

		//	RightTriggerPowerBar->SetPercent(Percent);
	}
}

void UHealthBarComponent::Set_SpeedBar_Percentage(float Percent)
{
	if (!SpeedBarWidget)
	{
		SpeedBarWidget = Cast<UHealthBar>(GetUserWidgetObject());
	}
	if (HealthBarWidget)
	{
		HealthBarWidget->SpeedBar->SetPercent(Percent);
	}
}

void UHealthBarComponent::Set_RightTriggerBar_Percentage(float Percent)
{
	if (!RightTriggerBarWidget)
	{
		RightTriggerBarWidget = Cast<UHealthBar>(GetUserWidgetObject());
	}
	if (RightTriggerBarWidget)
	{
		RightTriggerBarWidget->RightTriggerPowerBar->SetPercent(Percent);
	}
}

void UHealthBarComponent::Set_LeftTriggerBar_Percentage(float Percent)
{
	if (!LeftTriggerBarWidget)
	{
		LeftTriggerBarWidget = Cast<UHealthBar>(GetUserWidgetObject());
	}
	if (LeftTriggerBarWidget)
	{
		LeftTriggerBarWidget->LeftTriggerPowerBar->SetPercent(Percent);
	}
}
