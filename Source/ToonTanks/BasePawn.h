// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "BasePawn.generated.h"


UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	UStaticMeshComponent* GetTurretMesh() { return TurretMesh; };
protected:
	void RotateTurret(FVector LookAtTarget, float DeltaTime);
	  void Fire();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AExplosiveRound>ExplosiveRoundClass;
	//declaration



	protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCapsuleComponent *CapsuleComp;
	UPROPERTY (VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	
	 UStaticMeshComponent	*BaseMesh;
	 UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	 UStaticMeshComponent	*TurretMesh;
	 UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	 USceneComponent		*ProjectileSpawnPoint;
	 UPROPERTY(Category = "MovementProperties", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	 float TurretTurnRate = 200.0f;
	 UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	 class UParticleSystemComponent* OnDeathPFX;
public:
	ABasePawn* PlayerTank;//Idont like it should be called Target
	//UPROPERTY(Category = "PFX", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//UParticleSystemComponent* DeathPFX;

	USceneComponent *GetProjectileSpawnPoint() 
	{
		return ProjectileSpawnPoint;
	}
	UStaticMeshComponent* GetBaseMesh()
	{
		return BaseMesh;
	}
	class UCapsuleComponent *GetCapsuleComponent()
	{
		return CapsuleComp;
	}
	void HandleDestruction();


};
