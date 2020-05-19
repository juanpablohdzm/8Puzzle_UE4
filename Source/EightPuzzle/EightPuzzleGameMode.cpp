// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "EightPuzzleGameMode.h"
#include "EightPuzzlePlayerController.h"
#include "EightPuzzlePawn.h"

AEightPuzzleGameMode::AEightPuzzleGameMode()
{
	// no pawn by default
	DefaultPawnClass = AEightPuzzlePawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = AEightPuzzlePlayerController::StaticClass();
}
