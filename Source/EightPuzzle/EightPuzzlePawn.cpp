// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "EightPuzzlePawn.h"
#include "EightPuzzleBlock.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

AEightPuzzlePawn::AEightPuzzlePawn(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AEightPuzzlePawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AEightPuzzlePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("ResetVR", EInputEvent::IE_Pressed, this, &AEightPuzzlePawn::OnResetVR);
}

void AEightPuzzlePawn::CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult)
{
	Super::CalcCamera(DeltaTime, OutResult);

	OutResult.Rotation = FRotator(-90.0f, -90.0f, 0.0f);
}

void AEightPuzzlePawn::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}