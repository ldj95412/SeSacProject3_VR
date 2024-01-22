
#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Actor.h"
#include "LDJ_PickupActors.generated.h"

UCLASS()
class CITYSUBWAYTRAINMODULAR_API ALDJ_PickupActors : public AActor
{
	GENERATED_BODY()
	
public:	
	ALDJ_PickupActors();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* RootComp;

	UPROPERTY(EditAnywhere, Category="MySettings|Values")
	FVector locationOffset = FVector(0, 0, 10);

	UPROPERTY(EditAnywhere, Category="MySettings|Values")
	float throwPower = 100;

	UPROPERTY(EditAnywhere, Category="MySettings|Values")
	float rotPower = 1;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void Grabbed(class USkeletalMeshComponent* handMesh, EAttachmentRule attachmentRules);
	virtual void Released(FVector deltaPosition, FQuat deltaRotaion);
	virtual void LeftTriggerDoing(const FInputActionValue& value);
	virtual void LeftTriggerDoingCompleted(const FInputActionValue& value);
	virtual void RightTriggerDoing(const FInputActionValue& value);
	virtual void RightTriggerDoingCompleted(const FInputActionValue& value);
};
