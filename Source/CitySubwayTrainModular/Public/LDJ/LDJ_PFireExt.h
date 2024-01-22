// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LDJ/LDJ_PickupActors.h"
#include "LDJ_PFireExt.generated.h"

/**
 * 
 */
UCLASS()
class CITYSUBWAYTRAINMODULAR_API ALDJ_PFireExt : public ALDJ_PickupActors
{
	GENERATED_BODY()

	ALDJ_PFireExt();
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	// virtual void Grabbed(class USkeletalMeshComponent* handMesh, EAttachmentRule attachmentRules) override;
	// virtual void Released(FVector deltaPosition, FQuat deltaRotaion) override;
	virtual void LeftTriggerDoing(const FInputActionValue& value) override;
	virtual void LeftTriggerDoingCompleted(const FInputActionValue& value) override;
	virtual void RightTriggerDoing(const FInputActionValue& value) override;
	virtual void RightTriggerDoingCompleted(const FInputActionValue& value) override;
	
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* BodyComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* HoseComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* GripComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* PinComp;

	UPROPERTY(EditAnywhere)
	class USceneComponent* HoseLoc;

	UPROPERTY(EditAnywhere)
	class USceneComponent* SafePinLoc;

	int32 FireExtLevel;
	bool GrabHose = false;

	UPROPERTY(EditAnywhere)
	class ALDJ_VRPlayer* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings | Factory")
	TSubclassOf<class AActor> FireExtFactory;

	FTimerHandle Timerhandle;
	FVector PinTraceLoc;
	FQuat PinTraceQuat;

	bool DoOnceSound = false;
};
