// Fill out your copyright notice in the Description page of Project Settings.


#include "LDJ/LDJ_MoveComponent.h"

#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LDJ/LDJ_VRPlayer.h"

// Sets default values for this component's properties
ULDJ_MoveComponent::ULDJ_MoveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULDJ_MoveComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Player = Cast<ALDJ_VRPlayer>(GetOwner());
}


// Called every frame
void ULDJ_MoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULDJ_MoveComponent::SetupPlayerInputComponent(UEnhancedInputComponent* enhancedInputComponent)
{
	enhancedInputComponent->BindAction(IA_LeftThumbstick, ETriggerEvent::Triggered, this, &ULDJ_MoveComponent::PlayerMove);
	enhancedInputComponent->BindAction(IA_LeftThumbstick, ETriggerEvent::Completed, this, &ULDJ_MoveComponent::PlayerMoveComplete);
	enhancedInputComponent->BindAction(IA_RightThumbstick, ETriggerEvent::Triggered, this, &ULDJ_MoveComponent::PlayerRotate);
	enhancedInputComponent->BindAction(IA_RightThumbstick, ETriggerEvent::Completed, this, &ULDJ_MoveComponent::PlayerRotate);
}

void ULDJ_MoveComponent::PlayerMove(const FInputActionValue& value)
{
	FVector inputDir = FVector(value.Get<FVector2D>().X, value.Get<FVector2D>().Y, 0);
	FVector modifiedDir = Player->GetTransform().TransformVector(inputDir);
	Player->AddMovementInput(modifiedDir);
	GetWorld()->GetTimerManager().SetTimer(Handle,FTimerDelegate::CreateLambda([this]()->void
	{
		UGameplayStatics::PlaySound2D(GetWorld(), Player->FootStepSound, 5);
	}), 0.5, true);
}

void ULDJ_MoveComponent::PlayerMoveComplete(const FInputActionValue& value)
{
	GetWorld()->GetTimerManager().ClearTimer(Handle);
}

void ULDJ_MoveComponent::PlayerRotate(const FInputActionValue& value)
{
	FVector inputDir = FVector(value.Get<FVector2D>().X, value.Get<FVector2D>().Y, 0);
	Player->AddControllerYawInput(inputDir.X);
}

