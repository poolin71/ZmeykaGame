// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "MyActor.h"
#include "ZmeyBoss.h"
#include "Food.h"
#include "Components/InputComponent.h"
#include "Engine/Classes/Components/InputComponent.h"
#include "MenuWidget.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
	RootComponent = PawnCamera;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	SetActorRotation(FRotator(-90, 0, 0));
	CreateFood();
	CreateZmeykaActor();
	CreateZBossActor();
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Vertical", this, &AMyPawn::HandlePlayerVerticalInput);
	PlayerInputComponent->BindAxis("Horizontal", this, &AMyPawn::HandlePlayerHorizontalInput);
}

void AMyPawn::CreateZmeykaActor()
{
	MyActorActor = GetWorld()->SpawnActor<AMyActor>(MyActorActorClass, FTransform());
}

void AMyPawn::CreateZBossActor()
{
	ZmeyBossActor = GetWorld()->SpawnActor<AZmeyBoss>(ZmeyBossActorClass, FTransform());
}

void AMyPawn::CreateFood()
{
	int a, b;
	a = (-451) + rand() % 448;
	b = (-438) + rand() % 451;
	FVector NewLocationFood(a, b, 0);
	FTransform NewTransform(NewLocationFood);
	FoodActor = GetWorld()->SpawnActor<AFood>(FoodActorClass, NewTransform);
}

void AMyPawn::HandlePlayerVerticalInput(float value)
{
	if (IsValid(MyActorActor))
	{
		if (value > 0 && MyActorActor->LastMoveDirection!=EMovementDirection::DOWN)
		{
			MyActorActor->LastMoveDirection = EMovementDirection::UP;
		}
		else if (value < 0 && MyActorActor->LastMoveDirection != EMovementDirection::UP)
		{
			MyActorActor->LastMoveDirection = EMovementDirection::DOWN;
		}
	}
}

void AMyPawn::HandlePlayerHorizontalInput(float value)
{
	if (IsValid(MyActorActor))
	{
		if (value > 0 && MyActorActor->LastMoveDirection != EMovementDirection::LEFT)
		{
			MyActorActor->LastMoveDirection = EMovementDirection::RIGHT;
		}
		else if (value < 0 && MyActorActor->LastMoveDirection != EMovementDirection::RIGHT)
		{
			MyActorActor->LastMoveDirection = EMovementDirection::LEFT;
		}
	}
}