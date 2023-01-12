// Fill out your copyright notice in the Description page of Project Settings.


#include "ZmeykaElementBase.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "MyActor.h"
#include "ZmeyBoss.h"
#include "Teleport.h"
#include "Food.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "MenuWidget.h"

// Sets default values
AZmeykaElementBase::AZmeykaElementBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}

// Called when the game starts or when spawned
void AZmeykaElementBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AZmeykaElementBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AZmeykaElementBase::SetFirstElementType_Implementation()
{
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AZmeykaElementBase::HendleBeginOverlap);
}

void AZmeykaElementBase::Interact(AActor* Interactor, bool bIsHead)
{
	auto Snake = Cast<AMyActor>(Interactor); //получаем скастованный указатель на змейку
	if (IsValid(Snake)) //реализация элементов
	{
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
		Snake->Destroy(); //посылаем на змейку проигрышь змейки
	}
	if (bIsHead)
	{
		auto SnakeBoss = Cast<AZmeyBoss>(Interactor);
		if (IsValid(SnakeBoss)) //реализация элементов
		{
			SnakeOwner->MinusOne();
		}
	}
}

void AZmeykaElementBase::HendleBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	                                        AActor* OtherActor,
	                                        UPrimitiveComponent* OtherComp,
	                                        int32 OtherBodyIndex,
	                                        bool bfromSweep,
	                                        const FHitResult &SweepResult)
{
	if (IsValid(SnakeOwner)) //проверим валидность указателя на змейку
	{
		SnakeOwner->ZmeykaElementOverlap(this, OtherActor);
	}
}

void AZmeykaElementBase::ToggleCollision()
{
	if (MeshComponent->GetCollisionEnabled() == ECollisionEnabled::NoCollision) //текущий вид включения
	{
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}