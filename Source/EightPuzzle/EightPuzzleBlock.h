// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EightPuzzleBlock.generated.h"

/** A block that can be clicked */
UCLASS(minimalapi)
class AEightPuzzleBlock : public AActor
{
	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	/** StaticMesh component for the clickable block */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* BlockMesh;

	/** Text component for the score */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* ScoreText;

	int Number; 

public:
	AEightPuzzleBlock();

	/** Are we currently active? */
	bool bIsActive;

	/** Pointer to white material used on the focused block */
	UPROPERTY()
	class UMaterial* BaseMaterial;

	/** Grid that owns us */
	UPROPERTY()
	class AEightPuzzleBlockGrid* OwningGrid;

public:
	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }
	/** Returns BlockMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetBlockMesh() const { return BlockMesh; }
	/** Returns ScoreText **/
	FORCEINLINE class UTextRenderComponent* GetScoreText() const { return ScoreText; }
	/** Returns&Gets Number */
	FORCEINLINE int& GetNumber()  { return Number; }




};



