// Fill out your copyright notice in the Description page of Project Settings.

#include "ZmeyBoss.h"
#include <iostream>
#include <string>
#include "ZBossElementBase.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Interactable.h"

using namespace std;

// Sets default values
AZmeyBoss::AZmeyBoss()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize1 = 20.f;
	MovementSpeed2 = 1.f;
	LastMoveDirection2 = EMovementDirection2::LEFT2;
	prop_izm_tick = 0;
}

// Called when the game starts or when spawned
void AZmeyBoss::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MovementSpeed2);
	AddZBossElement(5);
}

// Called every frame
void AZmeyBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (prop_izm_tick)
	{
		Move2();
	}
	FVector MovementVector(ForceInitToZero);
	FVector mestonakh_golovy;
	FVector mestonakh_el_tela;
	int j;
	bool blok_smeny_napr;

	int i = 0 + rand() % 4;

	if (i == 0 && LastMoveDirection2 != EMovementDirection2::DOWN2)
	{
		mestonakh_golovy = ZBossElements[0]->GetActorLocation();
		mestonakh_golovy.X += (MovementVector.X + ElementSize1);
		j = 1;
		blok_smeny_napr = false;
		while (j < 5)
		{
			mestonakh_el_tela = ZBossElements[j]->GetActorLocation();
			if (mestonakh_golovy == mestonakh_el_tela)
			{
				/*GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Vperedi telo (UP2)"));*/
				blok_smeny_napr = true;
				break;
			}
			j++;
		}
		if (blok_smeny_napr == false)
		{
			LastMoveDirection2 = EMovementDirection2::UP2;
		}
	}
	if (i == 1 && LastMoveDirection2 != EMovementDirection2::UP2)
	{
		mestonakh_golovy = ZBossElements[0]->GetActorLocation();
		mestonakh_golovy.X -= (MovementVector.X + ElementSize1);
		j = 1;
		blok_smeny_napr = false;
		while (j < 5)
		{
			mestonakh_el_tela = ZBossElements[j]->GetActorLocation();
			if (mestonakh_golovy == mestonakh_el_tela)
			{
				/*GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Vperedi telo (DOWN2)"));*/
				blok_smeny_napr = true;
				break;
			}
			j++;
		}
		if (blok_smeny_napr == false)
		{
			LastMoveDirection2 = EMovementDirection2::DOWN2;
		}
	}
	if (i == 2 && LastMoveDirection2 != EMovementDirection2::RIGHT2)
	{
		mestonakh_golovy = ZBossElements[0]->GetActorLocation();
		mestonakh_golovy.Y -= (MovementVector.Y + ElementSize1);
		j = 1;
		blok_smeny_napr = false;
		while (j < 5)
		{
			mestonakh_el_tela = ZBossElements[j]->GetActorLocation();
			if (mestonakh_golovy == mestonakh_el_tela)
			{
				/*GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Vperedi telo (LEFT2)"));*/
				blok_smeny_napr = true;
				break;
			}
			j++;
		}
		if (blok_smeny_napr == false)
		{
			LastMoveDirection2 = EMovementDirection2::LEFT2;
		}
	}
	if (i == 3 && LastMoveDirection2 != EMovementDirection2::LEFT2)
	{
		mestonakh_golovy = ZBossElements[0]->GetActorLocation();
		mestonakh_golovy.Y += (MovementVector.Y + ElementSize1);
		j = 1;
		blok_smeny_napr = false;
		while (j < 5)
		{
			mestonakh_el_tela = ZBossElements[j]->GetActorLocation();
			if (mestonakh_golovy == mestonakh_el_tela)
			{
				/*GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Vperedi telo (RIGHT2)"));*/
				blok_smeny_napr = true;
				break;
			}
			j++;
		}
		if (blok_smeny_napr == false)
		{
			LastMoveDirection2 = EMovementDirection2::RIGHT2;
		}
	}
}

void AZmeyBoss::AddZBossElement(int ElementsNum1)
{
	for (int i = 0; i < ElementsNum1; ++i)
	{
		FVector NewLocation(ZBossElements.Num()*ElementSize1, 240, 0);
		FTransform NewTransform(NewLocation);
		AZBossElementBase* NewZmeykaElem = GetWorld()->SpawnActor<AZBossElementBase>(ZBossElementClass, NewTransform);
		NewZmeykaElem->SnakeOwner = this; //установление вручную значения "SnakeOwner"
		int32 ElemIndex = ZBossElements.Add(NewZmeykaElem);
		if (ElemIndex == 0)
		{
			NewZmeykaElem->SetFirstElementType();
		}
	}
}

// Реализация движения змейки-босса
void AZmeyBoss::Move2()
{
	FVector MovementVector2(ForceInitToZero);

	switch (LastMoveDirection2)
	{
	case EMovementDirection2::UP2:
		MovementVector2.X += ElementSize1;
		break;
	case EMovementDirection2::DOWN2:
		MovementVector2.X -= ElementSize1;
		break;
	case EMovementDirection2::LEFT2:
		MovementVector2.Y -= ElementSize1;
		break;
	case EMovementDirection2::RIGHT2:
		MovementVector2.Y += ElementSize1;
		break;
	}

	ZBossElements[0]->ToggleCollision();

	for (int i = ZBossElements.Num() - 1; i > 0; i--)
	{
		auto CurrentElement = ZBossElements[i];
		auto PrevElement = ZBossElements[i - 1];
		FVector PrevLocation = PrevElement->GetActorLocation();
		CurrentElement->SetActorLocation(PrevLocation);
	}

	ZBossElements[0]->AddActorWorldOffset(MovementVector2);
	ZBossElements[0]->ToggleCollision();
}

void AZmeyBoss::RandNaprav()
{
	int i = 0 + rand() % 3;

	if (i == 0)
	{
		LastMoveDirection2 = EMovementDirection2::UP2;
	}
	if (i == 1)
	{
		LastMoveDirection2 = EMovementDirection2::DOWN2;
	}
	if (i == 2)
	{
		LastMoveDirection2 = EMovementDirection2::LEFT2;
	}
	if (i == 3)
	{
		LastMoveDirection2 = EMovementDirection2::RIGHT2;
	}
}

void AZmeyBoss::GGlh1(AActor* otheMy1)
{
	int NewX = ZBossElements[0]->GetActorLocation().X;
	int NewY = ZBossElements[0]->GetActorLocation().Y;
	int NewZ = ZBossElements[0]->GetActorLocation().Z;

	if (NewY >= 470)
	{
		int NewNewY = NewY - NewY * 1.80;

		FVector chlen(NewX, NewNewY, NewZ);
		ZBossElements[0]->SetActorLocation(chlen);
	}
	if (NewY <= -470)
	{
		int NewNewY = NewY - NewY * 1.80;

		FVector chlen(NewX, NewNewY, NewZ);
		ZBossElements[0]->SetActorLocation(chlen);
	}
	if (NewX >= 470)
	{
		int NewNewX = NewX - NewX * 1.80;

		FVector chlen(NewNewX, NewY, NewZ);
		ZBossElements[0]->SetActorLocation(chlen);
	}
	if (NewX <= -470)
	{
		int NewNewX = NewX - NewX * 1.80;

		FVector chlen(NewNewX, NewY, NewZ);
		ZBossElements[0]->SetActorLocation(chlen);
	}
}

void AZmeyBoss::ZmeykaElementOverlap(AZBossElementBase* OverlappedElement, AActor* Other)
{
	if (IsValid(OverlappedElement)) //реализация метода
	{
		int32 ElemIndex;
		ZBossElements.Find(OverlappedElement, ElemIndex);
		if (IsValid(this))
		{
			bool bIsFirst = true; //проверка указателя на валидность/какой блок сколизился
			IInteractable* InteractableIntface = Cast<IInteractable>(Other); //указатель на наш интерфейс и скастовать наш актор к интерфейсу
			if (InteractableIntface) //указатель не нулевой
			{
				InteractableIntface->Interact(this, bIsFirst);
			}
		}
	}
}