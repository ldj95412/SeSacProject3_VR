// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LDJ/LDJ_PickupActors.h"
#include "LDJ_PCellPhone.generated.h"

/**
 * 
 */
UCLASS()
class CITYSUBWAYTRAINMODULAR_API ALDJ_PCellPhone : public ALDJ_PickupActors
{
	GENERATED_BODY()
	
	ALDJ_PCellPhone();
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void Grabbed(class USkeletalMeshComponent* handMesh, EAttachmentRule attachmentRules) override;
	virtual void Released(FVector deltaPosition, FQuat deltaRotaion) override;
	virtual void LeftTriggerDoing(const FInputActionValue& value) override;
	virtual void LeftTriggerDoingCompleted(const FInputActionValue& value) override;
	virtual void RightTriggerDoing(const FInputActionValue& value) override;
	virtual void RightTriggerDoingCompleted(const FInputActionValue& value) override;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* BodyComp;

	UPROPERTY(EditAnywhere)
	class USpotLightComponent* SpotComp;

	FTimerHandle Handle;
	float CurrentTime;
	bool CellphoneLevel = false;

	UPROPERTY()
	class ALDJ_VRPlayer* Player;

	bool bFlag = false;
};
