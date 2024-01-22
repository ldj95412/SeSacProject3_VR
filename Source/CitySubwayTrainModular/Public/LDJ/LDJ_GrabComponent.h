// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "LDJ_GrabComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CITYSUBWAYTRAINMODULAR_API ULDJ_GrabComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULDJ_GrabComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetupPlayerInputComponent(class UEnhancedInputComponent* enhancedInputComponent);

	class ALDJ_VRPlayer* Player;
	class ALDJ_PickupActors* CurrentObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")//IMC
	class UInputAction* IA_LeftGrip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")//IMC
	class UInputAction* IA_RightGrip;
	
	FVector DeltaLoc;
	FQuat DeltaQuat;

	void PlayerGrabLeft(const FInputActionValue& value);
	void PlayerReleaseLeft(const FInputActionValue& value);
	void PlayerGrabRight(const FInputActionValue& value);
	void PlayerReleaseRight(const FInputActionValue& value);
};
