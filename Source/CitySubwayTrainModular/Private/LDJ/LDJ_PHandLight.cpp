// Fill out your copyright notice in the Description page of Project Settings.


#include "LDJ/LDJ_PHandLight.h"

#include "EnhancedInputSubsystems.h"
#include "Components/BoxComponent.h"
#include "Components/SpotLightComponent.h"
#include "LDJ/LDJ_PickupComponent.h"

ALDJ_PHandLight::ALDJ_PHandLight()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetRelativeScale3D(FVector(0.03));
	RootComp->SetBoxExtent(FVector(16));

	LightComp = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight Component"));
	LightComp->SetupAttachment(RootComponent);
	LightComp->SetIntensity(0);
	LightComp->SetRelativeLocation(FVector(0,-2,5));
	LightComp->SetRelativeRotation(FRotator(0,-90,0));

	RootComp->SetSimulatePhysics(false);
	MeshComp->SetSimulatePhysics(false);
}

void ALDJ_PHandLight::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALDJ_PHandLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALDJ_PHandLight::Grabbed(USkeletalMeshComponent* handMesh, EAttachmentRule attachmentRules)
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

void ALDJ_PHandLight::Released(FVector deltaPosition, FQuat deltaRotaion)
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

void ALDJ_PHandLight::LeftTriggerDoing(const FInputActionValue& value)
{
	if (value.Get<float>() == 0) return;
	if (bFlipFlop)
	{
		LightComp->SetIntensity(0);
		bFlipFlop = false;
	}
	else
	{
		LightComp->SetIntensity(50000);
		bFlipFlop = true;
	}
}

void ALDJ_PHandLight::RightTriggerDoing(const FInputActionValue& value)
{
	if (value.Get<float>() == 0) return;
	if (bFlipFlop)
	{
		LightComp->SetIntensity(0);
		bFlipFlop = false;
	}
	else
	{
		LightComp->SetIntensity(50000);
		bFlipFlop = true;
	}
}


