// Fill out your copyright notice in the Description page of Project Settings.


#include "LDJ/LDJ_HandyBox.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "LDJ/LDJ_VRPlayer.h"

ALDJ_HandyBox::ALDJ_HandyBox()
{
	BodyComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Component"));
	BodyComp->SetupAttachment(RootComponent);

	CoverComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cover Component"));
	CoverComp->SetupAttachment(BodyComp);
	CoverComp->SetRelativeLocation(FVector(-14,11,-17));

	CoverHandle = CreateDefaultSubobject<USceneComponent>(TEXT("Cover Handle Origin"));
	CoverHandle->SetupAttachment(CoverComp);
	CoverHandle->SetRelativeLocation(FVector(25,5,18));

	RootComp->SetBoxExtent(FVector(15,10,19));
	RootComp->SetSimulatePhysics(false);
	RootComp->SetEnableGravity(false);
}

void ALDJ_HandyBox::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ALDJ_VRPlayer>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}

void ALDJ_HandyBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALDJ_HandyBox::Grabbed(USkeletalMeshComponent* handMesh, EAttachmentRule attachmentRules)
{
	
	auto Distance = FVector::Distance(CoverHandle->GetComponentLocation(), Player->RightHandComp->GetComponentLocation());

	if (Distance < 15)
	{
		GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([this]()->void
		{
			auto Rotate = UKismetMathLibrary::FindLookAtRotation(CoverComp->GetComponentLocation(),Player->RightHandComp->GetComponentLocation());
			CoverComp->SetRelativeRotation(FRotator(0,Rotate.Yaw - 20, 0));
		}),0.02,true);
	}
}

void ALDJ_HandyBox::Released(FVector deltaPosition, FQuat deltaRotaion)
{
	// DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	GetWorld()->GetTimerManager().ClearTimer(Handle);
}

void ALDJ_HandyBox::LeftTriggerDoing(const FInputActionValue& value)
{
	
}

void ALDJ_HandyBox::LeftTriggerDoingCompleted(const FInputActionValue& value)
{
	
}

void ALDJ_HandyBox::RightTriggerDoing(const FInputActionValue& value)
{
}

void ALDJ_HandyBox::RightTriggerDoingCompleted(const FInputActionValue& value)
{
}
