// Fill out your copyright notice in the Description page of Project Settings.


#include "LDJ/LDJ_WidgetBtnComponent.h"

#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "LDJ/LDJ_VRPlayer.h"

// Sets default values for this component's properties
ULDJ_WidgetBtnComponent::ULDJ_WidgetBtnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULDJ_WidgetBtnComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Player = Cast<ALDJ_VRPlayer>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}


// Called every frame
void ULDJ_WidgetBtnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULDJ_WidgetBtnComponent::SetupPlayerInputComponent(UEnhancedInputComponent* enhancedInputComponent)
{
	enhancedInputComponent->BindAction(IA_AButton, ETriggerEvent::Started, this, &ULDJ_WidgetBtnComponent::PressAButton);
	enhancedInputComponent->BindAction(IA_BButton, ETriggerEvent::Started, this, &ULDJ_WidgetBtnComponent::PressBButton);
	enhancedInputComponent->BindAction(IA_XButton, ETriggerEvent::Started, this, &ULDJ_WidgetBtnComponent::PressXButton);
	enhancedInputComponent->BindAction(IA_YButton, ETriggerEvent::Started, this, &ULDJ_WidgetBtnComponent::PressYButton);
}

void ULDJ_WidgetBtnComponent::PressAButton(const FInputActionValue& value)
{
	if (!bStarted)
	{
		bStarted++;
		Player->UIWidgetComp->SetMaterial(0, Player->UIPlane3);
	}
	else if(bStarted == 1)
	{
		bStarted++;
		Player->UIWidgetComp->SetMaterial(0, Player->UIPlane4);
		UGameplayStatics::PlaySound2D(GetWorld(), Player->UISound1, 2);
	}
	else if(bStarted > 1)
	{
		Player->UIWidgetComp->SetVisibility(true);
	}
}
void ULDJ_WidgetBtnComponent::PressBButton(const FInputActionValue& value)
{
	Player->UIWidgetComp->SetVisibility(false);
	if (!bStarted)
	{
		UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
	}
}

void ULDJ_WidgetBtnComponent::PressXButton(const FInputActionValue& value)
{
	UE_LOG(LogTemp,Warning, TEXT("X button Crouching"));
	Player->GetCapsuleComponent()->SetCapsuleHalfHeight(10);
}

void ULDJ_WidgetBtnComponent::PressYButton(const FInputActionValue& value)
{
	UE_LOG(LogTemp,Warning, TEXT("Y button Crouching"));
	Player->GetCapsuleComponent()->SetCapsuleHalfHeight(80);

}

