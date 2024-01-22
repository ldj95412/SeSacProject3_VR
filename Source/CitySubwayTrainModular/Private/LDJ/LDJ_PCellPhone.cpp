// Fill out your copyright notice in the Description page of Project Settings.


#include "LDJ/LDJ_PCellPhone.h"

#include "Components/BoxComponent.h"
#include "Components/SpotLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LDJ/LDJ_VRPlayer.h"

ALDJ_PCellPhone::ALDJ_PCellPhone()
{
	BodyComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Component"));
	BodyComp->SetupAttachment(RootComponent);
	BodyComp->SetRelativeLocation(FVector(0,0,-14));
	BodyComp->SetRelativeScale3D(FVector(0.1));

	SpotComp = CreateDefaultSubobject<USpotLightComponent>(TEXT("Spotlight Component"));
	SpotComp->SetupAttachment(BodyComp);
	SpotComp->SetRelativeLocation(FVector(-20,140,200));
	SpotComp->SetRelativeRotation(FRotator(0,-90,0));
	SpotComp->SetIntensity(0);
	SpotComp->SetLightColor(FLinearColor::Red);
	SpotComp->SetOuterConeAngle(3);

	RootComp->SetBoxExtent(FVector(8));
	RootComp->SetSimulatePhysics(false);
	RootComp->SetEnableGravity(false);
}

void ALDJ_PCellPhone::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<ALDJ_VRPlayer>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}

void ALDJ_PCellPhone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALDJ_PCellPhone::Grabbed(USkeletalMeshComponent* handMesh, EAttachmentRule attachmentRules)
{
	RootComp->SetSimulatePhysics(false);
	
	if (attachmentRules == EAttachmentRule::KeepWorld)
	{
		FAttachmentTransformRules rules = FAttachmentTransformRules::KeepWorldTransform;
		AttachToComponent(handMesh, rules);
	}
	// else if (attachmentRules == EAttachmentRule::SnapToTarget)
	// {
	// 	FAttachmentTransformRules rules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
	// 	AttachToComponent(handMesh, rules, FName("GrabSocket")); // 붙일 소켓 이름 
	// 	SetActorRelativeLocation(locationOffset);
	// }
}

void ALDJ_PCellPhone::Released(FVector deltaPosition, FQuat deltaRotaion)
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	RootComp->SetSimulatePhysics(false); //순서: Detach 후 Physics 켜주기

	// 던질때(Released될 때) 당시의 속도와 각속도를 추가해준다.
	if(deltaPosition.Size() > 0.05f)// 사람 손의 기본적인 움직임이 있어서 델타값이 0일 수는 없어서 0.05 이상일 때만
	{
		RootComp->AddImpulse(deltaPosition * throwPower);
		RootComp->AddTorqueInRadians(deltaRotaion.GetRotationAxis() * rotPower);
	}
}

void ALDJ_PCellPhone::LeftTriggerDoing(const FInputActionValue& value)
{
}

void ALDJ_PCellPhone::LeftTriggerDoingCompleted(const FInputActionValue& value)
{
	
}

void ALDJ_PCellPhone::RightTriggerDoing(const FInputActionValue& value)
{
	SpotComp->SetIntensity(5000);
	GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([this]()->void
	{
		CurrentTime += GetWorld()->GetDeltaSeconds();
		if (CurrentTime > 5)
		{
			SpotComp->SetLightColor(FLinearColor::Green);
			CellphoneLevel = true;
			
			Player->UIWidgetComp->SetMaterial(0, Player->UIPlane5);
			Player->UIWidgetComp->SetVisibility(true);
			if (!bFlag)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), Player->UISound2, 2);
				bFlag = true;
			}
		}
	}), GetWorld()->GetDeltaSeconds(), true);
}

void ALDJ_PCellPhone::RightTriggerDoingCompleted(const FInputActionValue& value)
{
	if (!CellphoneLevel)
	{
		CurrentTime = 0;
	}
	SpotComp->SetIntensity(0);
	GetWorld()->GetTimerManager().ClearTimer(Handle);
}
