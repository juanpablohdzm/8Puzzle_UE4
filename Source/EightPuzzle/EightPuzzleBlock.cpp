// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "EightPuzzleBlock.h"
#include "EightPuzzleBlockGrid.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"
#include <Components/TextRenderComponent.h>

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

AEightPuzzleBlock::AEightPuzzleBlock()
{

	PrimaryActorTick.bCanEverTick = true;

	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BaseMaterial;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"))
			, BaseMaterial(TEXT("/Game/Puzzle/Meshes/BaseMaterial.BaseMaterial"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(1.f,1.f,0.25f));
	BlockMesh->SetRelativeLocation(FVector(0.f,0.f,25.f));
	BlockMesh->SetMaterial(0, ConstructorStatics.BaseMaterial.Get());
	BlockMesh->SetupAttachment(DummyRoot);

	// Save a pointer to the orange material
	BaseMaterial = ConstructorStatics.BaseMaterial.Get();

	// Create static mesh component
	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText0"));
	ScoreText->SetTextRenderColor(FColor::Blue);
	ScoreText->SetupAttachment(DummyRoot);
}

#undef LOCTEXT_NAMESPACE