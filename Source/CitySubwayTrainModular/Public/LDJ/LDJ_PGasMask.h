// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LDJ/LDJ_PickupActors.h"
#include "LDJ_PGasMask.generated.h"

/**
 * 
 */
UCLASS()
class CITYSUBWAYTRAINMODULAR_API ALDJ_PGasMask : public ALDJ_PickupActors
{
	GENERATED_BODY()

	ALDJ_PGasMask();
	
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
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* CaseComp;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* PlasticComp;
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult & SweepResult);

	UPROPERTY()
	bool bReady = false;

	UPROPERTY()
	class ALDJ_VRPlayer* Player;
};
