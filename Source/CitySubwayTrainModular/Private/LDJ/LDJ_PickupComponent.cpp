

#include "LDJ/LDJ_PickupComponent.h"

#include "EnhancedInputComponent.h"
#include "LDJ/LDJ_PickupActors.h"
#include "LDJ/LDJ_VRPlayer.h"

ULDJ_PickupComponent::ULDJ_PickupComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void ULDJ_PickupComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ALDJ_VRPlayer>(GetOwner());
}


void ULDJ_PickupComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void ULDJ_PickupComponent::SetupPlayerInputComponent(UEnhancedInputComponent* enhancedInputComponent)
{
	enhancedInputComponent->BindAction(IA_LeftShoot, ETriggerEvent::Started, this, &ULDJ_PickupComponent::PlayerShootLeft);
	enhancedInputComponent->BindAction(IA_LeftShoot, ETriggerEvent::Completed, this, &ULDJ_PickupComponent::PlayerShootLeftCompleted);
	enhancedInputComponent->BindAction(IA_RightShoot, ETriggerEvent::Started, this, &ULDJ_PickupComponent::PlayerShootRight);
	enhancedInputComponent->BindAction(IA_RightShoot, ETriggerEvent::Completed, this, &ULDJ_PickupComponent::PlayerShootRightCompleted);
}

void ULDJ_PickupComponent::PlayerShootLeft(const FInputActionValue& value)
{
	if (Owner->LeftHandling)
	{
		Owner->LeftHandling->LeftTriggerDoing(value);
	}
	else if (Owner->RightHandling)
	{
		Owner->RightHandling->LeftTriggerDoing(value);
	}
}

void ULDJ_PickupComponent::PlayerShootLeftCompleted(const FInputActionValue& value)
{
	if (Owner->LeftHandling)
	{
		Owner->LeftHandling->LeftTriggerDoingCompleted(value);
	}
	else if (Owner->RightHandling)
	{
		Owner->RightHandling->LeftTriggerDoingCompleted(value);
	}
}

void ULDJ_PickupComponent::PlayerShootRight(const FInputActionValue& value)
{
	if (Owner->LeftHandling)
	{
		Owner->LeftHandling->RightTriggerDoing(value);
	}
	else if (Owner->RightHandling)
	{
		Owner->RightHandling->RightTriggerDoing(value);
	}
}

void ULDJ_PickupComponent::PlayerShootRightCompleted(const FInputActionValue& value)
{
	if (Owner->LeftHandling)
	{
		Owner->LeftHandling->RightTriggerDoingCompleted(value);
	}
	else if (Owner->RightHandling)
	{
		Owner->RightHandling->RightTriggerDoingCompleted(value);
	}
}

