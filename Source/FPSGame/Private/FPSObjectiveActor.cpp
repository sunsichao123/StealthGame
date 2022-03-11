// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSObjectiveActor.h"

#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSObjectiveActor::AFPSObjectiveActor()
{
	MeshCompo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshCompo"));
	MeshCompo->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshCompo;
	
	SphereCompo = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCompo"));
	SphereCompo->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCompo->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCompo->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	SphereCompo->SetupAttachment(MeshCompo);

	
}

// Called when the game starts or when spawned
void AFPSObjectiveActor::BeginPlay()
{
	Super::BeginPlay();
	PlayEffects();
}

void AFPSObjectiveActor::PlayEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, PickupFX, GetActorLocation());
}

void AFPSObjectiveActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	PlayEffects();

	AFPSCharacter* MyCharacter = Cast<AFPSCharacter>(OtherActor);
	if (MyCharacter)
	{
		MyCharacter->bIsCarryingObjective = true;

		Destroy();
	}
}

