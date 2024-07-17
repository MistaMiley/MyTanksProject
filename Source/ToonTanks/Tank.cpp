// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

#include "InputActionValue.h"

/* Add these include directories through the vVS gui
#include "../../../../../Program Files/Epic Games/UE_5.3/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/InputTriggers.h"
#include "../../../../../Program Files/Epic Games/UE_5.3/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
*/
ATank::ATank()
	: ABasePawn()
{
	PlayerControllerRef = nullptr;
	absdiff = 0.f;

	//create springarm
	TankSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("TankCameraArm"));
	//attach springarm to root
	TankSpringArm->SetupAttachment(RootComponent);

	FVector BarrelOffset(80, 0, 90);
//	TankProjectileSpawnPoint->AddLocalOffset(BarrelOffset);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("TankCamera"));
	//		//link the spring SpawnPoint to the root
	//	//Now link the camera to the springArm
	//	Camera->SetupAttachment(TankSpringArm);
	PowerToLeftTrack = PowerToRightTrack = TankAdvancement = 0.f;
};

//void ATank::Fire()
//{
//
//	if(ProjectileSpawnPoint)
//	{
//		
//		FVector projectileSpawnPointPos(ProjectileSpawnPoint->GetComponentLocation());
////#ifdef  TURRETDEBUG
//
//
//
//		DrawDebugSphere(GetWorld(), projectileSpawnPointPos, 25.f, 8, FColor::Green, false,3.f);
////#endif TURRETDEBUG
//	}
//	else
//	{
//		UE_LOG(LogTemp, Warning, TEXT("FirePressed & spawn point is null!"));
//	}
//
//}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
		Super::SetupPlayerInputComponent(PlayerInputComponent);
		//
		//	Legacy Input Bindings
		//
		PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);//tank can move
		PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn); // tank can turn
		PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed, this, &ATank::Fire);

		PlayerInputComponent->BindAxis(TEXT("LeftTrackPower"), this, &ATank::LeftTrackPower);//tank can move
		PlayerInputComponent->BindAxis(TEXT("RightTrackPower"), this, &ATank::RightTrackPower);//tank can move
		//if (UEnhancedInputComponent *EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
		//{
		//	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered,this, &ATank::MoveForward);
		//}
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());
	// Call the base class  
	//Super::BeginPlay();
	// 
//	//TankProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	//if (TankProjectileSpawnPoint)
	//Add Input Mapping Context
	//if (APlayerController *PlayerController = PlayerControllerRef;
		//Cast<APlayerController>(Controller))
		//{
		//if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		//{
		//	Subsystem->AddMappingContext(InputMapping, 0);
		//}
	//}

}

void ATank::Move(float Value)
{
//	UE_LOG(LogTemp, Warning, TEXT("LegacyMoveTriggered! %f"),Value);
	FVector DeltaLocation = FVector::ZeroVector;
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	DeltaLocation.X = Value*DeltaTime*Speed;
	AddActorLocalOffset(DeltaLocation,true);

}

void ATank::Turn(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	DeltaRotation.Yaw = Value * TurnRate * DeltaTime;
	AddActorLocalRotation(DeltaRotation,true);
}

void ATank::TurnLeft(float Value)
{
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	AddControllerYawInput(Value* TurnRate * DeltaTime);
}

void ATank::TurnRight(float Value)
{
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	AddControllerYawInput(-Value * TurnRate * DeltaTime);
}

void ATank::LeftTrackPower(float Value)
{
	if (Value <1.f)
	{
		PowerToLeftTrack = Value;
	//	Turn(Value);
	//	UE_LOG(LogTemp, Warning, TEXT("PowerToLeftTrack %f"),Value);
	}
}

void ATank::RightTrackPower(float Value)
{
	if (Value < 1.f)
	{
		PowerToRightTrack = Value;
	//	Turn(Value);
	//	UE_LOG(LogTemp, Warning, TEXT("PowerToRightTrack =%f"),Value);
	}
}
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Turn(-1.f);//-1turnsleft
	//return;
	if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(1, -1, FColor::Yellow, FString::Printf(TEXT("PowerToRightTrack:%s->"),*FString::SanitizeFloat(PowerToRightTrack)));
			GEngine->AddOnScreenDebugMessage(2, -1, FColor::Magenta, FString::Printf(TEXT("<-PowerToLeftTrack:%s"), *FString::SanitizeFloat(PowerToLeftTrack)));
			GEngine->AddOnScreenDebugMessage(3, -1, FColor::Cyan,	FString::Printf(TEXT("AbsoluteDifference%s"), *FString::SanitizeFloat(absdiff)));
		}
	//
	//TurnLeft(1.f);
	//return;
	if (PowerToRightTrack > PowerToLeftTrack)
	{
		Turn(absdiff);
	}
	else if(PowerToLeftTrack > PowerToRightTrack)
	{
		Turn(-absdiff);
	}
	//return;
	//calculate our movement no input no movement
	if ((PowerToLeftTrack > 0.f) && PowerToRightTrack > 0.f)
	{ 
		// the maximum difference will be 1 i.e one trigger depressed 1.f the other not 0.f
		absdiff = fabs(PowerToLeftTrack - PowerToRightTrack);
		TankAdvancement =FMath::Lerp(1.f, 0.f, absdiff);//afm  reward the smaller distance with higher speed
		//UE_LOG(LogTemp, Warning, TEXT("Tankadvancement  =%f"), TankAdvancement);
		//UE_LOG(LogTemp, Warning, TEXT("absdiff  =%f"), absdiff);
		Move(TankAdvancement);
	}
	

	if (PlayerControllerRef)
	{
		FHitResult hitResult;
		PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hitResult);
		//ECC_WorldStatic
		//PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldStatic, false, hitResult);
		if (hitResult.bBlockingHit)
		{

			DrawDebugSphere(GetWorld(), hitResult.Location, 10.f, 8, FColor::Red, false, -1.f);
			RotateTurret(hitResult.Location, DeltaTime);

		}
	}
	if (ProjectileSpawnPoint)
	{
	//	UE_LOG(LogTemp,Warning,TEXT("validproj spawn point"));
		FVector projectileSpawnPointPos(ProjectileSpawnPoint->GetComponentLocation());
#ifdef TURRETDEBUG
		DrawDebugSphere(GetWorld(), projectileSpawnPointPos, 50.f, 8, FColor::Green, true, -1);
#endif TURRETDEBUG

	}
	else
	{
	//	UE_LOG(LogTemp, Warning, TEXT("INvalidproj spawn point"));
	}
}
