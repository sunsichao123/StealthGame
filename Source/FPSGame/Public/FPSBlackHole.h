// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "FPSBlackHole.generated.h"

UCLASS()
class FPSGAME_API AFPSBlackHole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSBlackHole();

protected:
	UPROPERTY(VisibleAnywhere,Category="Componennts")
	UStaticMeshComponent* MeshComp;

	//InnerSphere destroy the actors
	UPROPERTY(VisibleAnywhere,Category="Components")
	USphereComponent* InnerSphereComponent;

	//OutSphere pulls the actors
	UPROPERTY(VisibleAnywhere,Category="Components")
	USphereComponent* OuterSphereComponent;

	//bind the overlap event
	UFUNCTION()
	void OverLapInnerSphere(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
