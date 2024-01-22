// Fill out your copyright notice in the Description page of Project Settings.


#include "VRHandAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"

void UVRHandAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{

	//1.FMath Ŭ���� �Լ��� �̿��� ��
	//currentPoseAlpha ������ ���� PoseAlpha ������ ���� �ǵ��� ������ �����Ѵ�.
	//CurrentPoseAlphaPoint_cpp = FMath::Lerp(CurrentPoseAlphaPoint_cpp, PoseAlphaPoint_cpp, DeltaSeconds * 13.0f);
	//CurrentPoseAlphaThumbUp_cpp = FMath::Lerp(CurrentPoseAlphaThumbUp_cpp, PoseAlphaThumbUp_cpp, DeltaSeconds * 13.0f);

	//2.KismetMathLibrary Ŭ���� �Լ��� �̿��� ��
	UKismetMathLibrary::FInterpTo(CurrentPoseAlphaPoint_cpp, PoseAlphaPoint_cpp, DeltaSeconds, 13.f);
	UKismetMathLibrary::FInterpTo(CurrentPoseAlphaThumbUp_cpp, PoseAlphaThumbUp_cpp, DeltaSeconds, 13.f);

	if (bMirror_cpp) {
		UE_LOG(LogTemp, Warning, TEXT("Left Thumb up: %.2f"), PoseAlphaThumbUp_cpp);
	}

}
