// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSLaunchPad.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSLaunchPad::AFPSLaunchPad()
{
	OverlapCompo = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapCompo"));
	OverlapCompo->SetBoxExtent(FVector(75,75,50));
	RootComponent = OverlapCompo;

	MeshCompo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshCompo->SetupAttachment(RootComponent);

	//bind the event
	OverlapCompo->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchPad::OverlapLaunchPad);

	LaunchStrength = 1500;
	LaunchPitchAngle = 35.0f;
}

void AFPSLaunchPad::OverlapLaunchPad(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FRotator LaunchDirection = GetActorRotation();
	LaunchDirection.Pitch += LaunchPitchAngle;
	FVector LaunchVelocity = LaunchDirection.Vector() * LaunchStrength;

	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	
	if (OtherActor)
	{
		//Launch Player. Both booleans give consistent launch velocity by ignoring the current player velocity
		OtherCharacter->LaunchCharacter(LaunchVelocity,true,true);

		//spawn FX
		UGameplayStatics::SpawnEmitterAtLocation(this, ActivateLaunchPadEffect, GetActorLocation());
	}

	//if not a player, check if it is a physical simulating actor that we can lauch
	else if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulse(LaunchVelocity,NAME_None,true);

		//spawn FX
		UGameplayStatics::SpawnEmitterAtLocation(this, ActivateLaunchPadEffect, GetActorLocation());
	}
}



