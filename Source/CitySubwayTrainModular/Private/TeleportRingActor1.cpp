// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportRingActor1.h"
#include "NiagaraComponent.h"

// Sets default values
ATeleportRingActor1::ATeleportRingActor1()
{
	PrimaryActorTick.bCanEverTick = false;

	ring_FX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Ring Effect"));
	ring_FX->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATeleportRingActor1::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATeleportRingActor1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

