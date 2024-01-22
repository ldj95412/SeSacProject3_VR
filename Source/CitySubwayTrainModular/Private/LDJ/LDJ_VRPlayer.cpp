

#include "LDJ/LDJ_VRPlayer.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "MotionControllerComponent.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "LDJ/LDJ_GrabComponent.h"
#include "LDJ/LDJ_MoveComponent.h"
#include "LDJ/LDJ_PickupComponent.h"
#include "LDJ/LDJ_WidgetBtnComponent.h"

ALDJ_VRPlayer::ALDJ_VRPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	//컴포넌트 생성부//
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComp->SetupAttachment(RootComponent);

	HmdMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HMD Mesh Component"));
	HmdMeshComp->SetupAttachment(CameraComp);

	LeftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Left Controller"));
	LeftController->SetupAttachment(RootComponent);
	LeftController->SetRelativeLocation(FVector(50, -30, -10));
	LeftController->SetTrackingMotionSource(FName("Left"));

	LeftHandComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Left Hand Mesh"));
	LeftHandComp->SetupAttachment(LeftController);
	LeftHandComp->SetRelativeRotation(FRotator(-90, -45, -180));

	RightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right Controller"));
	RightController->SetupAttachment(RootComponent);
	RightController->SetRelativeLocation(FVector(50, 30, -10));
	RightController->SetTrackingMotionSource(FName("Right"));
	
	RightHandComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Right Hand Mesh"));
	RightHandComp->SetupAttachment(RightController);
	RightHandComp->SetRelativeRotation(FRotator(90, 45, 0));

	UIWidgetComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plain Widget Component"));
	UIWidgetComp->SetupAttachment(CameraComp);
	UIWidgetComp->SetRelativeLocation(FVector(300, 0, 0));
	UIWidgetComp->SetRelativeRotation(FRotator(0,90,90));
	UIWidgetComp->SetRelativeScale3D(FVector(3));
	UIWidgetComp->SetCollisionProfileName(FName("NoCollision"));

	MoveComp = CreateDefaultSubobject<ULDJ_MoveComponent>(TEXT("Move Component"));
	GrabComp = CreateDefaultSubobject<ULDJ_GrabComponent>(TEXT("Grab Component"));
	PickComp = CreateDefaultSubobject<ULDJ_PickupComponent>(TEXT("Pickup Component"));
	WidgetBtnComp = CreateDefaultSubobject<ULDJ_WidgetBtnComponent>(TEXT("Widget Btn Component"));
	////

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->MaxWalkSpeed = 300;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialRef1(TEXT("/Game/LDJ/UI/Menu/WidgetTexture/M_LDJ_UI1.M_LDJ_UI1"));
	UIPlane1 = MaterialRef1.Object;
	
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialRef2(TEXT("/Game/LDJ/UI/Menu/WidgetTexture/M_LDJ_UI2.M_LDJ_UI2"));
	UIPlane2 = MaterialRef2.Object;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialRef3(TEXT("/Game/LDJ/UI/Menu/WidgetTexture/M_LDJ_UI3.M_LDJ_UI3"));
	UIPlane3 = MaterialRef3.Object;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialRef4(TEXT("/Game/LDJ/UI/Menu/WidgetTexture/M_LDJ_UI4.M_LDJ_UI4"));
	UIPlane4 = MaterialRef4.Object;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialRef5(TEXT("/Game/LDJ/UI/Menu/WidgetTexture/M_LDJ_UI5.M_LDJ_UI5"));
	UIPlane5 = MaterialRef5.Object;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialRef6(TEXT("/Game/LDJ/UI/Menu/WidgetTexture/M_LDJ_UI6.M_LDJ_UI6"));
	UIPlane6 = MaterialRef6.Object;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialRef7(TEXT("/Game/LDJ/UI/Menu/WidgetTexture/M_LDJ_UI7.M_LDJ_UI7"));
	UIPlane7 = MaterialRef7.Object;
}

void ALDJ_VRPlayer::BeginPlay()
{
	Super::BeginPlay();

	UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Stage);

	if (APlayerController* pc = GetWorld()->GetFirstPlayerController())
	{
		UEnhancedInputLocalPlayerSubsystem* subsys = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());

		if (subsys != nullptr && IMC_VRMapping != nullptr)
		{
			subsys->AddMappingContext(IMC_VRMapping, 0);
		}
	}
	UIWidgetComp->SetMaterial(0, UIPlane1);

	GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([this]()->void
	{
		UGameplayStatics::PlaySound2D(GetWorld(), CouchSound);
	}),5,true);
}

void ALDJ_VRPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALDJ_VRPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (enhancedInputComponent)
	{
		// 컴포넌트에 입력 이벤트 넘겨주기
		MoveComp->SetupPlayerInputComponent(enhancedInputComponent);
		GrabComp->SetupPlayerInputComponent(enhancedInputComponent);
		PickComp->SetupPlayerInputComponent(enhancedInputComponent);
		WidgetBtnComp->SetupPlayerInputComponent(enhancedInputComponent);
	}
	
}

