// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "EightPuzzleBlockGrid.h"
#include "EightPuzzleBlock.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"
#include <queue>
#include <../Plugins/Marketplace/TweenMaker/Source/TweenMaker/Public/TweenManagerComponent.h>
#include <../Plugins/Marketplace/TweenMaker/Source/TweenMaker/Public/TweenContainer.h>
#include <../Plugins/Marketplace/TweenMaker/Source/TweenMaker/Public/Tweens/TweenVector.h>



AEightPuzzleBlockGrid::AEightPuzzleBlockGrid()
{
	PrimaryActorTick.bCanEverTick = true;
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Set defaults
	Size = 3;
	BlockSpacing = 300.f;

	blocks = std::vector<AEightPuzzleBlock*>(9);
}


void AEightPuzzleBlockGrid::BeginPlay()
{
	Super::BeginPlay();	
}

void AEightPuzzleBlockGrid::SetupLayout(FString layout)
{
	// Number of blocks
	const int32 NumBlocks = Size * Size;

	if (blocks.size())
	{
		for (AEightPuzzleBlock* block : blocks)
		{
			if (block)
			{
				block->Destroy();
				block = nullptr;
			}
		}

	}

	// Loop to spawn each block
	for (int32 BlockIndex = 0; BlockIndex < NumBlocks; BlockIndex++)
	{
		const float XOffset = (BlockIndex / Size) * BlockSpacing; // Divide by dimension
		const float YOffset = (BlockIndex % Size) * BlockSpacing; // Modulo gives remainder

		// Make position vector, offset from Grid location
		const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

		// Spawn a block
		AEightPuzzleBlock* NewBlock = GetWorld()->SpawnActor<AEightPuzzleBlock>(PuzzleBlockClass, BlockLocation, FRotator(0, 0, 0));

		// Tell the block about its owner
		if (NewBlock != nullptr)
		{
			NewBlock->OwningGrid = this;
			char num = layout[BlockIndex];
			if (num == '0')
			{
				currentX = (BlockIndex / Size);
				currentY = (BlockIndex % Size);
				NewBlock->SetActorHiddenInGame(true);
			}

			int number = std::atoi(&num);
			start[(BlockIndex / Size)][(BlockIndex % Size)] = number;
			NewBlock->GetNumber() = number;
			NewBlock->GetScoreText()->SetText(FString::FromInt(NewBlock->GetNumber()));
			blocks[number] = NewBlock;
		}
	}
}



void AEightPuzzleBlockGrid::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AEightPuzzleBlockGrid::CalculatePath()
{
	std::priority_queue<Node*, std::vector<Node*>, Comp> list;
	gc.clear();
	int row[] = { 1, 0, -1, 0 };
	int col[] = { 0, -1, 0, 1 };
	int finish[3][3] = { {0,1,2}, {3,4,5} ,{6,7,8} };

	Node* node = new Node();
	memcpy(node->matrix, start, sizeof(start));
	node->Initialize(nullptr,currentX,currentY, currentX, currentY,0);
	node->CalculateCost(finish);

	list.push(node);
	gc.push_back(node);

	while (!list.empty())
	{
		node = list.top();
		list.pop();
		if (!node->cost)
		{			
			while (node->parent)
			{
				node->parent->child = node;
				node = node->parent;
			}
			DisplayGraphics(node->child);
						
			return;
		}
		for (size_t i = 0; i < 4; i++)
		{
			if (IsNodePossible(node->x + row[i], node->y + col[i]))
			{
				Node* adjacent = new Node();
				adjacent->Initialize(node, node->x, node->y, node->x + row[i], node->y + col[i], node->level + 1);
				adjacent->CalculateCost(finish);
				list.push(adjacent);
				gc.push_back(adjacent);
			}
		}
	}
}

void AEightPuzzleBlockGrid::DisplayGraphics(Node* node)
{
	node->matrix;
	UTweenContainer* container = UTweenManagerComponent::CreateTweenContainerStatic();
	UTweenVector* move = container->AppendTweenMoveActorTo(nullptr, FVector::ZeroVector);
	for (size_t x = 0; x < Size; x++)
	{
		for (size_t y = 0; y < Size; y++)
		{
			const FVector Location = GetActorLocation() + FVector(x * BlockSpacing, y * BlockSpacing, 0);
			AEightPuzzleBlock* block = blocks[node->matrix[x][y]];
			//UE_LOG(LogTemp, Warning, TEXT("Block, X: %d Y: %d  Location:%s"), (int)x, (int)y, *block->GetActorLocation().ToString());
			if (!FMath::IsNearlyZero((block->GetActorLocation() - Location).Size()))
			{
				//UE_LOG(LogTemp, Warning, TEXT("X %i, Y %i"), x, y);
				move = container->JoinTweenMoveActorTo(block, Location);
			}
// 			else
// 			{
// 				GEngine->AddOnScreenDebugMessage(x + y * Size, 5.0f, FColor::Blue, FString("Distance is almost zero"));
// 			}
		}
	}

	container->OnTweenContainerEndDelegate.BindLambda([&, node](UTweenContainer* move)
	{
		if (!node) return;

		if (node->child)
		{
			DisplayGraphics(node->child);
		}
		else
		{
			for (Node* n : gc)
			{
				delete n;
			}
			gc.clear();
		}
	});
}

void AEightPuzzleBlockGrid::SolvePuzzle()
{
	CalculatePath();		
}

