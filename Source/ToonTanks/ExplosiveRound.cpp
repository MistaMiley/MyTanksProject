// Fill out your copyright notice in the Description page of Project Settings.
#define DEBUG_HIT (1)

#include "ExplosiveRound.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
/// <summary>
/// Constructor:Sets default values
/// NOTICE WE LIVE JUST UNDER THE #INCLUDES
/// </summary>
AExplosiveRound::AExplosiveRound()
{
	PrimaryActorTick.bCanEverTick = false;
	//create the mesh for our shell mesh
	ShellMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT(" ShellMesh"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement") );
	if(ProjectileMovement)
	{		
		ProjectileMovement->MaxSpeed  = 1300.0f;
		ProjectileMovement->InitialSpeed = 1300.0f;
	}

	if (ShellMesh)
	{
	}
	//set the mesh as our root
	RootComponent = ShellMesh;
	SmokeTrailPFX = CreateDefaultSubobject< UParticleSystemComponent>(TEXT("TrailPFX"));
	if (SmokeTrailPFX)
	{
		
		SmokeTrailPFX->SetupAttachment(RootComponent);
	}
}

/// <summary>
/// BeginPlay - Called when the game starts or when spawned
/// </summary>
void AExplosiveRound::BeginPlay()
{
	//UE_LOG(LogTemp, Warning, (TEXT("Launching Explosive Round")));
	Super::BeginPlay();
	//link the OnComponentHit EVENT to our onHit class Method
	ShellMesh->OnComponentHit.AddDynamic(this, &AExplosiveRound::OnHit);

}

// Called every frame
void AExplosiveRound::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
/// <summary>
/// OnHit callback 
/// </summary>
/// <param name="HitComp"></param>
/// <param name="OtherActor"></param>
/// <param name="OtherComp"></param>
/// <param name="NormalImpulse"></param>
/// <param name="Hit"></param>
void AExplosiveRound::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
	bool Im_finnaBlow = false;
	if (FVector::Parallel(Hit.ImpactNormal, FVector::UpVector))
	{
		Im_finnaBlow = true;
	}
#ifdef DEBUG_HIT



	if (OtherComp)
	{
	//	UE_LOG(LogTemp, Warning, TEXT("On HIT! otherComponment =%s"), *OtherComp->GetName());
	}

	if(OtherActor)
	{
	//	UE_LOG(LogTemp, Warning, TEXT("On HIT! OtherActor =%s"), *OtherActor->GetName());
	}
	//UE_LOG(LogTemp, Warning, TEXT("fHitResultNormal%s"), *Hit.ImpactNormal.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Engine UpNormal%s"), *FVector::UpVector.ToString());
	if(FVector::Parallel(Hit.ImpactNormal, FVector::UpVector))
	{
	//	UE_LOG(LogTemp, Warning, TEXT("!ImpactNormal &Engine UpNormal are Parallel!!!Yay"));
	}
	else
	{
	//	UE_LOG(LogTemp, Warning, TEXT("!ImpactNormal &Engine UpNormal are NOT Parallel!!!BOO!"));
		//we can blow this up now!
	}
#endif // DEBUG_HIT
	auto MyOwner = GetOwner();
	if (!MyOwner)
	{
		//Destroy();
		return;
	}
	if (FVector::Parallel(Hit.ImpactNormal, FVector::UpVector))
	{

	}
	else
	{
		//Destroy();
		//return;
	}
	auto MyOwnersInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();
	if (OtherComp)
		{
	//		UE_LOG(LogTemp, Warning, TEXT("On HIT!")); UE_LOG(LogTemp, Warning, TEXT("otherComponment =%s"), *OtherComp->GetName());
		}
	if (OtherActor && OtherActor!= MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor,Damage, MyOwnersInstigator,this,DamageTypeClass);
	//	UE_LOG(LogTemp, Warning, TEXT("ActorHIT Applying Damage!")); UE_LOG(LogTemp, Warning, TEXT("otheActor =%s"), *OtherActor->GetName());
	}
}





