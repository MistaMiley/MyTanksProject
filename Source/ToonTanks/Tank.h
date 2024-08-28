// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "InputActionValue.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public  ABasePawn
{
	GENERATED_BODY()
public:
	ATank();
	//{
	//	TankProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Tank_ProjectileSpawnPoint"));
	//}
	//void Fire();
//	void MoveForward(const  FInputActionValue& Value);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
//protected:
public:
		virtual void BeginPlay()override;
		void HandleDestruction();
		int32 GetNumPickupsCollected();
		void IncrementPickupCount();
private:
	UPROPERTY()
	class UHealthComponent *CachedHealth;
	//Speed of the  vehicle
	UPROPERTY(Category = "MovementProperties", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Speed = 20.0f;
	//TurnSpeed of the  vehicle
	UPROPERTY(Category = "MovementProperties", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float TurnRate = 200.0f;
	int32 PickupsCollected;
	UPROPERTY(Category = "MovementProperties", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))

	float MinTrackPower = 0.5f;
	void Move(float Value);
	void Turn(float Value);
	void TurnLeft(float Value);
	void TurnRight(float Value);
	void LeftTrackPower(float Value);
	void RightTrackPower(float Value);
	float PowerToLeftTrack;
	float PowerToRightTrack;
	float TankAdvancement;
	float absdiff;
	UPROPERTY(Category = "Components",	VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent *TankSpringArm;
	UPROPERTY(Category = "Components",	VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent	* Camera;
	
	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UHealthBarComponent *HealthBarWidget;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	//UInputAction* TriggerPullAction;

	//void Fire();
public:
	class APlayerController *PlayerControllerRef; 
	class APlayerController* GetTankPlayerController() 
	{ 
		return PlayerControllerRef; 
	}
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
