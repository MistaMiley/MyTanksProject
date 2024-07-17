// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
class ParticleSystemComponent;
#include "ExplosiveRound.generated.h"


UCLASS()
class TOONTANKS_API AExplosiveRound : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosiveRound();
private:
	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent	*ShellMesh;
	UPROPERTY(Category = "Movement", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent *ProjectileMovement;
	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit);

	UPROPERTY(EditAnywhere)
	float Damage = 30.f;
	UPROPERTY(Category = "Components", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent	*SmokeTrailPFX;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
