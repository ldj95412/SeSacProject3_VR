// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LDJ_PickUpInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULDJ_PickUpInterface : public UInterface
{
	GENERATED_BODY()
};

class CITYSUBWAYTRAINMODULAR_API ILDJ_PickUpInterface
{
	GENERATED_BODY()

public:
	virtual void Pickupasdf() = 0;
};
