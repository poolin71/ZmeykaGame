// Fill out your copyright notice in the Description page of Project Settings.

#include "Teleport.h"
#include "Engine/World.h"
#include "MyActor.h"
#include "ZmeyBoss.h"
#include "Food.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "ZmeykaElementBase.h"
#include <iostream>
#include <ctime>

// Sets default values
ATeleport::ATeleport()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Score = 0;
}

// Called when the game starts or when spawned
void ATeleport::BeginPlay()
{
	Super::BeginPlay();
}

void ATeleport::SpawnObject(FTransform NewTransform)
{
	AActor* SpawnedFoodRef = GetWorld()->SpawnActor<AActor>(ActorToSpawn, NewTransform);
}

void ATeleport::SpawnObject1(FTransform NewTransform1)
{
	AActor* SpawnedFoodRef = GetWorld()->SpawnActor<AActor>(ActorToSpawn1, NewTransform1);
}

// Called every frame
void ATeleport::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleport::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = Cast<AMyActor>(Interactor);
		auto SnakBoss = Cast<AZmeyBoss>(Interactor);

		if (IsValid(Snake))
		{
			Snake->GGlh(otheMy1);

			Score++;

			int a = (-421) + rand() % 849;
			int b = (-428) + rand() % 848;
			int numbers[3] = { 430, -420, a };
			int numbers1[3] = { 410, -410, b };
			int value = numbers[rand() % 3];
			int value1 = numbers1[rand() % 3];

			//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::FromInt(f.value));

			if (Score % 2 == 0)
			{

				if (value == -420)
				{

					FVector NewLocationFood1(value, b, 10);
					FVector NewLocationFood(value, b, 20);
					FVector NewLocationFood2(290, 370, -10);
					FTransform NewTransform1(NewLocationFood1);
					FTransform NewTransform(NewLocationFood);
					SpawnObject1(NewTransform1);

					GetWorld()->GetTimerManager().SetTimer(_loopTimerHandle, [=]()
						{
							SpawnObject(NewTransform);
						}, 1.f, false);
				}

				if (value == 430)
				{
					FVector NewLocationFood1(430, b, 10);
					FVector NewLocationFood(430, b, 20);
					FTransform NewTransform1(NewLocationFood1);
					FTransform NewTransform(NewLocationFood);
					SpawnObject1(NewTransform1);

					GetWorld()->GetTimerManager().SetTimer(_loopTimerHandle, [=]()
						{
							SpawnObject(NewTransform);
						}, 1.f, false);
				}

				if (value == a)
				{
					value1 = numbers1[rand() % 2];
					FVector NewLocationFood1(a, value1, 10);
					FVector NewLocationFood(a, value1, 20);
					FTransform NewTransform1(NewLocationFood1);
					FTransform NewTransform(NewLocationFood);
					SpawnObject1(NewTransform1);

					GetWorld()->GetTimerManager().SetTimer(_loopTimerHandle, [=]()
						{
							SpawnObject(NewTransform);
						}, 1.f, false);
				}
			}
		}
		if (IsValid(SnakBoss))
		{
			SnakBoss->GGlh1(otheMy2);
		}
	}
}