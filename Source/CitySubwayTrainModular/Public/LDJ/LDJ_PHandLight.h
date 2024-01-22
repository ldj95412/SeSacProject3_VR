// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LDJ/LDJ_PickupActors.h"
#include "LDJ_PHandLight.generated.h"

/**
 * 
 */
UCLASS()
class CITYSUBWAYTRAINMODULAR_API ALDJ_PHandLight : public ALDJ_PickupActors
{
	GENERATED_BODY()

public:	
	ALDJ_PHandLight();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void Grabbed(class USkeletalMeshComponent* handMesh, EAttachmentRule attachmentRules) override;
	virtual void Released(FVector deltaPosition, FQuat deltaRotaion) override;
	virtual void LeftTriggerDoing(const FInputActionValue& value) override;
	virtual void RightTriggerDoing(const FInputActionValue& value) override;
	
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere)
	class USpotLightComponent* LightComp;
	
	bool bFlipFlop = false;
	
};
