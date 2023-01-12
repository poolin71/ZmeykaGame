// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "MyActor.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "ZmeykaElementBase.h"
#include <iostream>
#include <ctime>
#include "BonusUskoreniye.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyActor::StaticClass(), FoundActors);
	for (AActor* TActor : FoundActors)
	{
		AMyActor* MyActor = Cast<AMyActor>(TActor);
		if (MyActor != nullptr)
		{
			int posl_el_zmey = MyActor->ZmeykaElements.Num() - 1;
			Rasp_posl_el = MyActor->ZmeykaElements[posl_el_zmey]->GetActorLocation();
		}
	}
}

void AFood::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = Cast<AMyActor>(Interactor);
		if (IsValid(Snake))
		{
			int i = 1 + rand() % 100;

			if (i <= 90)
			{
				Snake->AddZmeykaElement(Rasp_posl_el);
				Destroy();
				int a, b;
				a = (-451) + rand() % 448;
				b = (-438) + rand() % 451;
				FVector NewLocationFood(a, b, 0);
				FTransform NewTransform(NewLocationFood);
				FoodActor = GetWorld()->SpawnActor<AFood>(FoodActorClass, NewTransform);
			}
			if (i >= 91)
			{
				Destroy();
				int a, b;
				a = (-451) + rand() % 448;
				b = (-438) + rand() % 451;
				FVector NewLocationFood(a, b, 0);
				FTransform NewTransform(NewLocationFood);
				BonusActor = GetWorld()->SpawnActor<ABonusUskoreniye>(BonusActorClass, NewTransform);
			}
		}
	}
}