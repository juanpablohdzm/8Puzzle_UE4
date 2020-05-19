// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <string>
#include <algorithm>
#include <vector>
#include "EightPuzzleBlockGrid.generated.h"


struct Node
{
	Node* parent;

	Node* child;

	// stores matrix 
	int matrix[3][3];

	// stores blank tile coordinates 
	int x, y;

	// stores the number of misplaced tiles 
	int cost;

	// stores the number
	int level;

	void Initialize(Node* p, int _x, int _y, int newX,int newY, int _level)
	{
		child = nullptr;
		parent = p;
		if (p)
		{
			memcpy(matrix, p->matrix, sizeof(p->matrix));
		}
		std::swap(matrix[_x][_y], matrix[newX][newY]);
		x = newX;
		y = newY;
		level = _level; 
		cost = 0;

	}

	void CalculateCost(const int finish[3][3])
	{
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				if (matrix[i][j] != finish[i][j])
					cost++;
			}
		}
	}
};

struct Comp
{
	bool operator()(const Node* lhs, const Node* rhs) const
	{
		return (lhs->cost + lhs->level) > (rhs->cost + rhs->level);
	}
};

/** Class used to spawn blocks and manage score */
UCLASS(minimalapi)
class AEightPuzzleBlockGrid : public AActor
{
	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Grid, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

public:
	AEightPuzzleBlockGrid();

	/** Number of blocks along each side of grid */
	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	int32 Size;

	/** Spacing of blocks */
	UPROPERTY(Category=Grid, EditAnywhere, BlueprintReadOnly)
	float BlockSpacing;

	UPROPERTY(Category=Grid, EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class AEightPuzzleBlock> PuzzleBlockClass;

protected:
	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface
	virtual void Tick(float DeltaSeconds) override;

	virtual void CalculatePath();

	virtual void DisplayGraphics(Node* node);

	virtual bool IsNodePossible(int x, int y) { return (x >= 0 && x < Size && y >= 0 && y < Size); }

public:
	UFUNCTION(BlueprintCallable, Category = Grid)
	void SetupLayout(FString layout);

	UFUNCTION(BlueprintCallable, Category = Grid)
	void SolvePuzzle();

	/** Returns DummyRoot subobject **/
	FORCEINLINE class USceneComponent* GetDummyRoot() const { return DummyRoot; }

private:
	std::vector<class AEightPuzzleBlock*> blocks;


	int currentX,currentY;

	std::string Start;
	int start[3][3];
	std::vector<Node*> gc;


};



