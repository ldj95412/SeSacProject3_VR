// Fill out your copyright notice in the Description page of Project Settings.


#include "LDJ/LDJ_PGasMask.h"

#include "Components/BoxComponent.h"
#include "LDJ/LDJ_VRPlayer.h"

ALDJ_PGasMask::ALDJ_PGasMask()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetRelativeScale3D(FVector(0.002));
	MeshComp->SetRelativeLocation(FVector(3,2,0));
	CaseComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Case Component"));
	CaseComp->SetupAttachment(MeshComp);
	MeshComp->SetVisibility(false);
	CaseComp->SetVisibility(false);

	PlasticComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plastic Component"));
	PlasticComp->SetupAttachment(RootComponent);

	RootComp->SetBoxExtent(FVector(10,10,25));
	RootComp->SetGenerateOverlapEvents(false);
	MeshComp->SetGenerateOverlapEvents(false);
	CaseComp->SetGenerateOverlapEvents(false);
	PlasticComp->SetGenerateOverlapEvents(false);
}

void ALDJ_PGasMask::BeginPlay()
{
	Super::BeginPlay();
	RootComp->OnComponentBeginOverlap.AddDynamic(this, &ALDJ_PGasMask::OnBeginOverlap);
	Player = Cast<ALDJ_VRPlayer>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}

void ALDJ_PGasMask::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALDJ_PGasMask::LeftTriggerDoing(const FInputActionValue& value)
{
	
}

void ALDJ_PGasMask::LeftTriggerDoingCompleted(const FInputActionValue& value)
{
	PlasticComp->SetVisibility(false);
	MeshComp->SetVisibility(true);
	CaseComp->SetVisibility(true);
	bReady = true;
}

void ALDJ_PGasMask::RightTriggerDoing(const FInputActionValue& value)
{
	RootComp->SetGenerateOverlapEvents(true);
}

void ALDJ_PGasMask::RightTriggerDoingCompleted(const FInputActionValue& value)
{
	RootComp->SetGenerateOverlapEvents(true);
	GetWorld()->GetTimerManager().ClearTimer(Player->Handle);
	Player->UIWidgetComp->SetMaterial(0, Player->UIPlane7);
	Player->UIWidgetComp->SetVisibility(true);
	this->Destroy();
	
}

void ALDJ_PGasMask::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Player->UIWidgetComp->SetMaterial(0, Player->UIPlane7);
	Player->UIWidgetComp->SetVisibility(true);
	auto Temp = Cast<ALDJ_VRPlayer>(OtherActor);
	if (Temp && bReady == true)
	{
		//위젯
		GetWorld()->GetTimerManager().ClearTimer(Player->Handle);
		this->Destroy();
	}
}
