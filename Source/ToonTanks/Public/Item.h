// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "Item.generated.h"

class UPrimativeComponent;
//to make em more fancy
class USphereComponent;
class UNiagaraComponent;

enum class EItemState : uint8
{
	EIS_Hovering,
	EIS_Equipped
};

UCLASS()
class TOONTANKS_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	UFUNCTION(BlueprintCallable, Category = "item")
	static int32 GetInstanceCount();
	/** Overlapping Sphere*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "item| Collision") 
	class USphereComponent* CollisionVolume;

	/**BaseMeshComponent*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "item| Mesh")
	UStaticMeshComponent* Mesh;
	/** Toggles Rotation*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item| ItemProperties")
	bool bRotate;
	/** Rate Mesh Rotates*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item| ItemProperties")
	float RotationRate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float Amplitude = 37.5f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float TimeConstant = 5.f;

	UFUNCTION(BlueprintPure)
	float TransformedSin();

	UFUNCTION(BlueprintPure)
	float TransformedCos();



	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void SpawnPickupSystem();
	virtual void SpawnPickupSound();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	/* items physics prescence*/
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "itemProperties", meta = (AllowPrivateAccess = "true"))
	

	EItemState ItemState = EItemState::EIS_Hovering;



	//UPROPERTY(EditAnywhere)
	//UNiagaraComponent* ItemEffect;

	//UPROPERTY(EditAnywhere)
	USoundBase* PickupSound;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float RunningTime;

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* PickupEffect;
	static int32 Item_InstanceCount;
public:

};
