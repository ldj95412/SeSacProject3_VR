
#pragma once

#include "CoreMinimal.h"
#include "LDJ_PickUpInterface.h"
#include "GameFramework/Character.h"
#include "LDJ_VRPlayer.generated.h"

UCLASS()
class CITYSUBWAYTRAINMODULAR_API ALDJ_VRPlayer : public ACharacter 
{
	GENERATED_BODY()

public:
	ALDJ_VRPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//부착 컴포넌트//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Components")
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UStaticMeshComponent* HmdMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UMotionControllerComponent* LeftController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class USkeletalMeshComponent* LeftHandComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class UMotionControllerComponent* RightController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class USkeletalMeshComponent* RightHandComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Widget")
	class UStaticMeshComponent* UIWidgetComp;
	////

	//입력 연동//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")//IMC
	class UInputMappingContext* IMC_VRMapping;

	//기능 컴포넌트//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class ULDJ_MoveComponent* MoveComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class ULDJ_GrabComponent* GrabComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class ULDJ_PickupComponent* PickComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Components")
	class ULDJ_WidgetBtnComponent* WidgetBtnComp;

	UPROPERTY()
	class ALDJ_PickupActors* LeftHandling;
	
	UPROPERTY()
	class ALDJ_PickupActors* RightHandling;

	//마테리얼
	UPROPERTY()
	class UMaterialInterface* UIPlane1;

	UPROPERTY()
	class UMaterialInterface* UIPlane2;

	UPROPERTY()
	class UMaterialInterface* UIPlane3;

	UPROPERTY()
	class UMaterialInterface* UIPlane4;

	UPROPERTY()
	class UMaterialInterface* UIPlane5;

	UPROPERTY()
	class UMaterialInterface* UIPlane6;

	UPROPERTY()
	class UMaterialInterface* UIPlane7;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Sounds")
	class USoundBase* UISound1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Sounds")
	class USoundBase* UISound2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Sounds")
	class USoundBase* UISound3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Sounds")
	class USoundBase* FootStepSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MySettings|Sounds")
	class USoundBase* CouchSound;

	FTimerHandle Handle;
};
