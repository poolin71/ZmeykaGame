// Fill out your copyright notice in the Description page of Project Settings.


#include "Sharikunichtozhitel.h"
#include "MyActor.h"
#include "ZmeykaElementBase.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"

// Sets default values
ASharikunichtozhitel::ASharikunichtozhitel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize1 = 100.f;
	MovementSpeed1 = 10.f;
}

// Called when the game starts or when spawned
void ASharikunichtozhitel::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASharikunichtozhitel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move1(DeltaTime);

	int NewX = GetActorLocation().X;
	int NewY = GetActorLocation().Y;
	int NewZ = GetActorLocation().Z;

	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString::FromInt(NewX));

	if (NewY <= -409)
	{
		LastMoveDirection1 = EMovementDirection1::RIGHT;
	}

	if (NewY == 408 && LastMoveDirection1 == EMovementDirection1::RIGHT)
	{
		Destroy();
	}

	if (NewX >= 429)
	{
		LastMoveDirection1 = EMovementDirection1::DOWN;
	}

	if (NewX == -418 && LastMoveDirection1 == EMovementDirection1::DOWN)
	{
		Destroy();
	}

	if (NewY >= 409)
	{
		LastMoveDirection1 = EMovementDirection1::LEFT;
	}

	if (NewY == -408 && LastMoveDirection1 == EMovementDirection1::LEFT)
	{
		Destroy();
	}

	if (NewX <= -419)
	{
		LastMoveDirection1 = EMovementDirection1::UP;
	}

	if (NewX == 428 && LastMoveDirection1 == EMovementDirection1::UP)
	{
		Destroy();
	}
}

void ASharikunichtozhitel::Interact(AActor * Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = Cast<AMyActor>(Interactor);
		if (IsValid(Snake))
		{
			Snake->MinusTwo();

			Destroy();
		}
	}
}

void ASharikunichtozhitel::Move1(float DeltaTime)
{
	FVector MovementVector1(ForceInitToZero);
	float MovementSpeedDelta1 = MovementSpeed1 * DeltaTime;

	switch (LastMoveDirection1)
	{
	case EMovementDirection1::UP:
		MovementVector1.X += MovementSpeedDelta1;
		break;
	case EMovementDirection1::DOWN:
		MovementVector1.X -= MovementSpeedDelta1;
		break;
	case EMovementDirection1::RIGHT:
		MovementVector1.Y += MovementSpeedDelta1;
		break;
	case EMovementDirection1::LEFT:
		MovementVector1.Y -= MovementSpeedDelta1;
		break;
	}

	AddActorWorldOffset(MovementVector1);
}

