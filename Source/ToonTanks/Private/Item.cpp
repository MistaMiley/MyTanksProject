// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "../Tank.h"

//initialise our static
int32 AItem::Item_InstanceCount = 0;
// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("ItemMesh"));
	
	//SetRootComponent(ItemMesh);
	CollisionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionVolume"));
	RootComponent = CollisionVolume;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	bRotate = false;
	RotationRate = 45.f;
	CollisionVolume->SetGenerateOverlapEvents(true);
	CollisionVolume->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}
int32 AItem::GetInstanceCount()
{
	return Item_InstanceCount;
}
// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	Item_InstanceCount++;
	UE_LOG(LogTemp, Warning,TEXT("InstanceCount =%d"), Item_InstanceCount)
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this,&AItem::OnSphereOverlap);//who you gonna  call!
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this,&AItem::OnSphereEndOverlap);
}

float AItem::TransformedSin()
{
	return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}

float AItem::TransformedCos()
{
	return Amplitude * FMath::Cos(RunningTime * TimeConstant);
}




void AItem::SpawnPickupSystem()
{
	if (PickupEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			this,
			PickupEffect,
			GetActorLocation()
		);
	}
}

void AItem::SpawnPickupSound()
{
	if (PickupSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(
			this,
			PickupSound,
			GetActorLocation()
		);
	}
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RunningTime += DeltaTime;
	if(bRotate)
	{
		FRotator Rotation = GetActorRotation();
	}

	if (ItemState == EItemState::EIS_Hovering)
	{
		AddActorWorldOffset(FVector(0.f, 0.f, TransformedSin()));
	}

}

void AItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!OtherActor) return;
	UE_LOG(LogTemp, Warning, TEXT("HEY!!OnSphereOverlap!"));
	//AFM 20/08/24 CAST OTHER ACTOR TO ATANK& INCREMENT PICKUPS COLLECTED
	ATank *playerTank = Cast<ATank>(OtherActor);
	if (playerTank)
	{
		playerTank->IncrementPickupCount();
		Destroy();//outta here
	}
}

void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("EndingSphereOverlap!"));
	ATank* playerTank = Cast<ATank>(OtherActor);
	if (playerTank)
	{
	//	playerTank->IncrementPickupCount();
	}
}



