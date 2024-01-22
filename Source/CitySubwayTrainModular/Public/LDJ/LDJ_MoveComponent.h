// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "LDJ_MoveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CITYSUBWAYTRAINMODULAR_API ULDJ_MoveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULDJ_MoveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetupPlayerInputComponent(class UEnhancedInputComponent* enhancedInputComponent);

	class ALDJ_VRPlayer* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")//IMC
	class UInputAction* IA_LeftThumbstick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")//IMC
	class UInputAction* IA_RightThumbstick;

	void PlayerMove(const FInputActionValue& value);
	void PlayerMoveComplete(const FInputActionValue& value);
	void PlayerRotate(const FInputActionValue& value);

	bool FootstepOnce;
	FTimerHandle Handle;
};
