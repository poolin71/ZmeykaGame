// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "ZmeyBoss.h"
#include "ZmeykaElementBase.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Teleport.h"
#include "Food.h"
#include <iostream>
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "MenuWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.f;
	MovementSpeed1 = 0.7;
	LastMoveDirection = EMovementDirection::DOWN;
	prop_izm_tick = 0;
	prop_sozd_perv_el = 0;
	score2 = -1;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MovementSpeed1);
	FVector NewLocation1(0, 0, 0);
	AddZmeykaElement(NewLocation1, 5);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (prop_izm_tick)
	{
		Move();
	}
}

void AMyActor::AddZmeykaElement(FVector Rasp_posl_el, int ElementsNum)
{
	for (int i = 0; i < ElementsNum; ++i)
	{
		FVector* NewLocation1 = 0;
		if (ZmeykaElements.Num() <= ElementsNum && prop_sozd_perv_el == 0)
		{
			/*GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("Pervie elementi sozdani"));*/
			FVector NewLocation(ZmeykaElements.Num() * ElementSize, 0, 0);
			NewLocation1 = &NewLocation;
		}
		else
		{
			NewLocation1 = &Rasp_posl_el;
		}
		FTransform NewTransform(*NewLocation1);
		AZmeykaElementBase* NewZmeykaElem = GetWorld()->SpawnActor<AZmeykaElementBase>(ZmeykaElementClass, NewTransform);
		NewZmeykaElem->SnakeOwner = this; //установление вручную значения "SnakeOwner"
		int32 ElemIndex = ZmeykaElements.Add(NewZmeykaElem);
		if (ElemIndex == 0)
		{
			NewZmeykaElem->SetFirstElementType();
		}
	}
	prop_sozd_perv_el = 1;
}

void AMyActor::Move()
{
	FVector MovementVector(ForceInitToZero);

	switch (LastMoveDirection)
	{
	case EMovementDirection::UP:
		MovementVector.X += ElementSize;
		break;
	case EMovementDirection::DOWN:
		MovementVector.X -= ElementSize;
		break;
	case EMovementDirection::LEFT:
		MovementVector.Y += ElementSize;
		break;
	case EMovementDirection::RIGHT:
		MovementVector.Y -= ElementSize;
		break;
	}

	ZmeykaElements[0]->ToggleCollision();

	for (int i = ZmeykaElements.Num() - 1; i > 0; i--)
	{
		auto CurrentElement = ZmeykaElements[i];
		auto PrevElement = ZmeykaElements[i - 1];
		FVector PrevLocation = PrevElement->GetActorLocation();
		CurrentElement->SetActorLocation(PrevLocation);
	}

	ZmeykaElements[0]->AddActorWorldOffset(MovementVector);
	ZmeykaElements[0]->ToggleCollision();
}

void AMyActor::ZmeykaElementOverlap(AZmeykaElementBase* OverlappedElement, AActor* Other)
{
	if (IsValid(OverlappedElement)) //реализация метода
	{
		int32 ElemIndex;
		ZmeykaElements.Find(OverlappedElement, ElemIndex);
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

void AMyActor::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto ZmeykaElem = Cast<AFood>(Interactor);
		if (IsValid(ZmeykaElem))
		{
			ZmeykaElem->Destroy();
		}
		auto SnakBoss = Cast<AZmeyBoss>(Interactor);
		if (IsValid(SnakBoss))
		{
			MinusOne();
		}
	}
}

void AMyActor::GGlh(AActor* otheMy)
{
	int NewX = ZmeykaElements[0]->GetActorLocation().X;
	int NewY = ZmeykaElements[0]->GetActorLocation().Y;
	int NewZ = ZmeykaElements[0]->GetActorLocation().Z;

	if (NewY >= 470)
	{
		int NewNewY = NewY - NewY * 1.80;

		FVector chlen(NewX, NewNewY, NewZ);
		ZmeykaElements[0]->SetActorLocation(chlen);
	}

	if (NewY <= -470)
	{
		int NewNewY = NewY - NewY * 1.80;

		FVector chlen(NewX, NewNewY, NewZ);
		ZmeykaElements[0]->SetActorLocation(chlen);
	}

	if (NewX >= 470)
	{
		int NewNewX = NewX - NewX * 1.80;

		FVector chlen(NewNewX, NewY, NewZ);
		ZmeykaElements[0]->SetActorLocation(chlen);
	}

	if (NewX <= -470)
	{
		int NewNewX = NewX - NewX * 1.80;

		FVector chlen(NewNewX, NewY, NewZ);
		ZmeykaElements[0]->SetActorLocation(chlen);
	}
}

void AMyActor::MinusOne()
{
	if (ZmeykaElements.Num() == 1)
	{
		Destroy();
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AZmeyBoss::StaticClass(), FoundActors);
		for (AActor* TActor : FoundActors)
		{
			AZmeyBoss* ZmeyBoss = Cast<AZmeyBoss>(TActor);
			if (ZmeyBoss != nullptr)
			{
				ZmeyBossActor = ZmeyBoss;
			}
		}
		ZmeyBossActor->Destroy();
		TArray<UUserWidget*> FoundUserWidget;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundUserWidget, UMenuWidget::StaticClass());
		for (UUserWidget* TUserWidget : FoundUserWidget)
		{
			UMenuWidget* MenuWidget = Cast<UMenuWidget>(TUserWidget);
			if (MenuWidget != nullptr)
			{
				MenuWidgetWidget = MenuWidget;
			}
		}
		MenuWidgetWidget->vkl_tret_swit();
	}
	else
	{
		ZmeykaElements[ZmeykaElements.Num() - 1]->Destroy();
		ZmeykaElements.RemoveAt(ZmeykaElements.Num() - 1);
	}
}

void AMyActor::MinusTwo()
{
	if (ZmeykaElements.Num() <= 2)
	{
		Destroy();
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AZmeyBoss::StaticClass(), FoundActors);
		for (AActor* TActor : FoundActors)
		{
			AZmeyBoss* ZmeyBoss = Cast<AZmeyBoss>(TActor);
			if (ZmeyBoss != nullptr)
			{
				ZmeyBossActor = ZmeyBoss;
			}
		}
		ZmeyBossActor->Destroy();
		TArray<UUserWidget*> FoundUserWidget;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundUserWidget, UMenuWidget::StaticClass());
		for (UUserWidget* TUserWidget : FoundUserWidget)
		{
			UMenuWidget* MenuWidget = Cast<UMenuWidget>(TUserWidget);
			if (MenuWidget != nullptr)
			{
				MenuWidgetWidget = MenuWidget;
			}
		}
		MenuWidgetWidget->vkl_tret_swit();
	}
	else
	{
		for (int i = 0; i <= 1; i++)
		{
			ZmeykaElements[ZmeykaElements.Num() - 1]->Destroy();
			ZmeykaElements.RemoveAt(ZmeykaElements.Num() - 1);
		}
	}
}