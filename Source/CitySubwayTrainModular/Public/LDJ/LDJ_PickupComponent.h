
#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "LDJ_PickupComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CITYSUBWAYTRAINMODULAR_API ULDJ_PickupComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULDJ_PickupComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetupPlayerInputComponent(class UEnhancedInputComponent* enhancedInputComponent);

	class ALDJ_VRPlayer* Owner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")
	class UInputAction* IA_LeftShoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings|Inputs")
	class UInputAction* IA_RightShoot;

	void PlayerShootLeft(const FInputActionValue& value);
	void PlayerShootLeftCompleted(const FInputActionValue& value);
	void PlayerShootRight(const FInputActionValue& value);
	void PlayerShootRightCompleted(const FInputActionValue& value);
};
