
#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "LDJ_WidgetBtnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CITYSUBWAYTRAINMODULAR_API ULDJ_WidgetBtnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULDJ_WidgetBtnComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetupPlayerInputComponent(class UEnhancedInputComponent* enhancedInputComponent);

	UPROPERTY()
	class ALDJ_VRPlayer* Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")
	class UInputAction* IA_AButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")
	class UInputAction* IA_BButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")
	class UInputAction* IA_XButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")
	class UInputAction* IA_YButton;

	void PressAButton(const FInputActionValue& value);
	void PressBButton(const FInputActionValue& value);
	void PressXButton(const FInputActionValue& value);
	void PressYButton(const FInputActionValue& value);

	int32 bStarted = 0; 

};
