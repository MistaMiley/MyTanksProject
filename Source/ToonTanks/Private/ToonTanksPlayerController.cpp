// Fill out your copyright notice in the Description page of Project Settings.

#include "ToonTanksPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/UserWidget.h"


void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
	if (bPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}
	bShowMouseCursor = bPlayerEnabled;
}

void AToonTanksPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (HUDOverlayAsset)
	{
	HUDOverlay = CreateWidget<UUserWidget>(this, 
	HUDOverlayAsset);
	HUDOverlay->AddToViewport();
	HUDOverlay->SetVisibility(ESlateVisibility::Visible);
}
}
