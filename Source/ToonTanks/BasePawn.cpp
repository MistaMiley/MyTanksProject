// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Tank.h"
#include "Components/CapsuleComponent.h"
#include"Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "ExplosiveRound.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
	PlayerTank = nullptr;

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	CapsuleComp->SetupAttachment(RootComponent);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(CapsuleComp);
	//make BaseMesh the root;
	//RootComponent = CapsuleComp;
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BaseMesh);
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	if (ProjectileSpawnPoint)
	{	
		FVector BarrelOffset(000.f);
		//FVector BarrelOffset(200000.f, 100.f, 92000.f);
		ProjectileSpawnPoint->AddLocalOffset(BarrelOffset);

		ProjectileSpawnPoint->SetupAttachment(TurretMesh);
	
	}
}

void ABasePawn::RotateTurret(FVector LookAtTarget, float DeltaTime)
{
	if (TurretMesh)
	{
		FVector toPos(LookAtTarget); FVector fromPos(TurretMesh->GetComponentLocation());
			FVector ToTargetVector(toPos - fromPos );//simples direction = to - from
			//create a zero'd rotation and set with our yaw!
			FRotator CurrentTurretRotation(TurretMesh->GetComponentRotation());
			FRotator TargetTurretRotation(0.f); 
			TargetTurretRotation.Yaw = ToTargetVector.Rotation().Yaw;
			TurretMesh->SetWorldRotation( FMath::RInterpTo(CurrentTurretRotation, TargetTurretRotation, DeltaTime, TurretTurnRate));
	}
}

void ABasePawn::Fire()
{

	if (ProjectileSpawnPoint)
	{

		FVector projectileSpawnPointPos(ProjectileSpawnPoint->GetComponentLocation());
		FRotator ProjectilSpawnPointRotation(ProjectileSpawnPoint->GetComponentRotation());



		DrawDebugSphere(GetWorld(), projectileSpawnPointPos, 25.f, 8, FColor::Green, false, 3.f);
		
		//spawn shell
		auto Shell = GetWorld()->SpawnActor<AExplosiveRound>(ExplosiveRoundClass, projectileSpawnPointPos, ProjectilSpawnPointRotation);
		Shell->SetOwner(this);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("FirePressed & spawn point is null!"));
	}

};



// Called when the game starts or when spawned

// Called every frame
//void ABasePawn::Tick(float DeltaTime)
//{
	//Super::Tick(DeltaTime);
	//FVector DeltaLocation(0.f);
	//DeltaLocation.X = 2.f;
	//AddActorLocalOffset(DeltaLocation);

//};

// Called to bind functionality to input
//void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent); 
//
//}

