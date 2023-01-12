// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusUskoreniye.h"
#include "Engine/World.h"
#include "MyActor.h"
#include "Food.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Engine/World.h"

// Sets default values
ABonusUskoreniye::ABonusUskoreniye()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABonusUskoreniye::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABonusUskoreniye::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//Ниже бонус который увеличивает скорость
void ABonusUskoreniye::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead) //реализация функционала
	{
		auto Snake = Cast<AMyActor>(Interactor); //скастовать интеракт к змейке
		if (IsValid(Snake))
		{
			Snake->SetActorTickInterval(0.1F); //добавление 1 элемента
			Destroy();
			
			GetWorld()->GetTimerManager().SetTimer(_loopTimerHandle1, [=]()
				{
					Snake->SetActorTickInterval(1.f);
				}, 5.f, false);

			int a, b;
			a = (-451) + rand() % 448;
			b = (-438) + rand() % 451;
			FVector NewLocationFood(a, b, 20);
			FTransform NewTransform(NewLocationFood);
			FoodActor1 = GetWorld()->SpawnActor<AFood>(FoodActorClass1, NewTransform);
		}
	}
}