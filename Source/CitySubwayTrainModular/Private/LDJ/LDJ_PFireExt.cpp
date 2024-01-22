// Fill out your copyright notice in the Description page of Project Settings.


#include "LDJ/LDJ_PFireExt.h"

#include "MotionControllerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LDJ/LDJ_VRPlayer.h"

ALDJ_PFireExt::ALDJ_PFireExt()
{
	PrimaryActorTick.bCanEverTick = true;

	BodyComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Component"));
	BodyComp->SetupAttachment(RootComponent);
	BodyComp->SetRelativeLocation(FVector(0,0,-20));
	
	HoseComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hose Component"));
	HoseComp->SetupAttachment(BodyComp);
	
	GripComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Grip Component"));
	GripComp->SetupAttachment(BodyComp);
	
	PinComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pin Component"));
	PinComp->SetupAttachment(GripComp);

	HoseLoc = CreateDefaultSubobject<USceneComponent>(TEXT("Hose Origin"));
	HoseLoc->SetupAttachment(HoseComp);
	HoseLoc->SetRelativeLocation(FVector(-2,0,43.81f));
	HoseLoc->SetRelativeRotation(FRotator(0,180,0));

	SafePinLoc = CreateDefaultSubobject<USceneComponent>(TEXT("Pin Origin"));
	SafePinLoc->SetupAttachment(GripComp);
	SafePinLoc->SetRelativeLocation(FVector(0,0,45));
}

void ALDJ_PFireExt::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<ALDJ_VRPlayer>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}

void ALDJ_PFireExt::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (GrabHose)
	{
		FVector StartPnt = HoseLoc->GetComponentLocation();
		FVector EndPnt = Player->LeftHandComp->GetSocketLocation(FName("WaterShoot"));
		DrawDebugLine(GetWorld(),StartPnt, EndPnt, FColor::Black, false, -1, 0, 2);
	}
}

void ALDJ_PFireExt::LeftTriggerDoing(const FInputActionValue& value)
{
	auto Distance = FVector::Distance(SafePinLoc->GetComponentLocation(), Player->LeftHandComp->GetComponentLocation());

	UE_LOG(LogTemp, Warning, TEXT("FireExt Pin Test : %f"), Distance);
	
	if(Distance < 15 && FireExtLevel == 0)
	{
		PinComp->SetVisibility(false);
	}

	if (FireExtLevel > 0)
	{
		HoseComp->SetVisibility(false);
		GrabHose = true;
	}
}

void ALDJ_PFireExt::LeftTriggerDoingCompleted(const FInputActionValue& value)
{
	FireExtLevel++;
	if (FireExtLevel > 0 && GrabHose)
	{
		HoseComp->SetVisibility(true);
		GrabHose = false;
	}
}

void ALDJ_PFireExt::RightTriggerDoing(const FInputActionValue& value)
{
	if (FireExtLevel > 0 && GrabHose)
	{
		FTransform SpawnTransform = Player->LeftHandComp->GetSocketTransform(FName("WaterShoot"));
		GetWorld()->SpawnActor<AActor>(FireExtFactory,SpawnTransform);
		Player->UIWidgetComp->SetMaterial(0, Player->UIPlane6);
		Player->UIWidgetComp->SetVisibility(false);
		if (!DoOnceSound)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), Player->UISound3, 2);
			Player->UIWidgetComp->SetVisibility(true);
			DoOnceSound = true;
		}
	}
}

void ALDJ_PFireExt::RightTriggerDoingCompleted(const FInputActionValue& value)
{
	
}
