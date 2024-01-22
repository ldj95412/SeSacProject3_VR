

#include "LDJ/LDJ_GrabComponent.h"

#include "EnhancedInputComponent.h"
#include "LDJ/LDJ_PickupActors.h"
#include "LDJ/LDJ_VRPlayer.h"

ULDJ_GrabComponent::ULDJ_GrabComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void ULDJ_GrabComponent::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ALDJ_VRPlayer>(GetOwner());
}


void ULDJ_GrabComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void ULDJ_GrabComponent::SetupPlayerInputComponent(UEnhancedInputComponent* enhancedInputComponent)
{
	enhancedInputComponent->BindAction(IA_LeftGrip, ETriggerEvent::Triggered, this, &ULDJ_GrabComponent::PlayerGrabLeft);
	enhancedInputComponent->BindAction(IA_LeftGrip, ETriggerEvent::Completed, this, &ULDJ_GrabComponent::PlayerReleaseLeft);
	enhancedInputComponent->BindAction(IA_RightGrip, ETriggerEvent::Triggered, this, &ULDJ_GrabComponent::PlayerGrabRight);
	enhancedInputComponent->BindAction(IA_RightGrip, ETriggerEvent::Completed, this, &ULDJ_GrabComponent::PlayerReleaseRight);
}

void ULDJ_GrabComponent::PlayerGrabLeft(const FInputActionValue& value)
{
	if (CurrentObject) return;
	FHitResult hitInfo;
	FVector startLoc = Player->LeftHandComp->GetComponentLocation();
	FVector endLoc = startLoc + Player->LeftHandComp->GetRightVector() * 50.0f;

	if (GetWorld()->LineTraceSingleByProfile(hitInfo, startLoc, endLoc, FName("PickUp")))
	{
		CurrentObject = Cast<ALDJ_PickupActors>(hitInfo.GetActor());

		if (CurrentObject)
		{
			CurrentObject->Grabbed(Player->LeftHandComp, EAttachmentRule::KeepWorld);
			Player->LeftHandling = CurrentObject;
		}
	}
}

void ULDJ_GrabComponent::PlayerReleaseLeft(const FInputActionValue& value)
{
	// 물체를 잡고있을때만 실행
	if (!CurrentObject) return;

	CurrentObject->Released(DeltaLoc, DeltaQuat);
	CurrentObject = nullptr;
	Player->LeftHandling = CurrentObject;
}

void ULDJ_GrabComponent::PlayerGrabRight(const FInputActionValue& value)
{
	if (CurrentObject) return;
	FHitResult hitInfo;
	FVector startLoc = Player->RightHandComp->GetComponentLocation();
	FVector endLoc = startLoc + Player->RightHandComp->GetRightVector() * 50.0f;

	if (GetWorld()->LineTraceSingleByProfile(hitInfo, startLoc, endLoc, FName("PickUp")))
	{
		CurrentObject = Cast<ALDJ_PickupActors>(hitInfo.GetActor());

		if (CurrentObject)
		{
			CurrentObject->Grabbed(Player->RightHandComp, EAttachmentRule::KeepWorld);
			Player->RightHandling = CurrentObject;
			UE_LOG(LogTemp,Warning,TEXT("Right Grab"));
		}
	}
}

void ULDJ_GrabComponent::PlayerReleaseRight(const FInputActionValue& value)
{
	// 물체를 잡고있을때만 실행
	if (!CurrentObject) return;
	CurrentObject->Released(DeltaLoc, DeltaQuat);
	CurrentObject = nullptr;
	Player->RightHandling = CurrentObject;
}

