

#include "LDJ/LDJ_PickupActors.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/BoxComponent.h"
#include "LDJ/LDJ_MoveComponent.h"
#include "LDJ/LDJ_PickupComponent.h"

ALDJ_PickupActors::ALDJ_PickupActors()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Root Component"));
	SetRootComponent(RootComp);
	RootComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComp->SetCollisionProfileName(FName("Pickup"));
	RootComp->SetSimulatePhysics(false);
	RootComp->SetEnableGravity(true);
	RootComp->SetBoxExtent(FVector(50));
}

void ALDJ_PickupActors::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALDJ_PickupActors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALDJ_PickupActors::Grabbed(USkeletalMeshComponent* handMesh, EAttachmentRule attachmentRules)
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

void ALDJ_PickupActors::Released(FVector deltaPosition, FQuat deltaRotaion)
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

void ALDJ_PickupActors::LeftTriggerDoing(const FInputActionValue& value)
{
}

void ALDJ_PickupActors::LeftTriggerDoingCompleted(const FInputActionValue& value)
{
}

void ALDJ_PickupActors::RightTriggerDoing(const FInputActionValue& value)
{
	UE_LOG(LogTemp,Warning,TEXT("Right Handling"));
}

void ALDJ_PickupActors::RightTriggerDoingCompleted(const FInputActionValue& value)
{
}

