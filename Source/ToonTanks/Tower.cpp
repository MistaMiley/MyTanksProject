// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void ATower::Tick(float DeltaTime)
{
	//fire the souper!
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), TargetRange, 8, FColor::Yellow, false, -1.f);
	if (PlayerTank)
	{
		FVector PlayerTankPos(PlayerTank->GetActorLocation());
		//visualise myself & my range
		FVector ToPlayerTankVector(PlayerTankPos - GetActorLocation());
		if (ToPlayerTankVector.Length() <= TargetRange)
		{
			//show that target is in range
			{
				//use a scaled down target sphere to show we are being targetted
				DrawDebugSphere(GetWorld(), PlayerTankPos, TargetRange*.25f, 8, FColor::Red, false, -1.f);
				RotateTurret(PlayerTankPos, DeltaTime);
				//set target in range
				bTargetInRange = true;
			}		

		}
		else
		{
			bTargetInRange = false;
		}
	}		
		{


	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	//get the tank the player is controlling
	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
	//if (!PlayerTank) return;

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate,true);
}

 //void ATower::Fire()
 //{

	//UE_LOG(LogTemp, Warning, TEXT("Tower Fire!!"));
	//if (GetProjectileSpawnPoint())
	//{

	//	FVector projectileSpawnPointPos(GetProjectileSpawnPoint()->GetComponentLocation());
	//	//#ifdef  TURRETDEBUG

	//	DrawDebugSphere(GetWorld(), projectileSpawnPointPos, 25.f, 8, FColor::Green, false, 3.f);
	//	//#endif TURRETDEBUG
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("FirePressed & spawn point is null!"));
	//}

 //}

void ATower::CheckFireCondition()
{
	if (!PlayerTank)return;
	if (bTargetInRange)
	{
		Fire();
	}
}
