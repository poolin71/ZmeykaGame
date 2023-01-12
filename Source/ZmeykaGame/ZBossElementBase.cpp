// Fill out your copyright notice in the Description page of Project Settings.


#include "ZBossElementBase.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "MyActor.h"
#include "ZmeyBoss.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "MenuWidget.h"

// Sets default values
AZBossElementBase::AZBossElementBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent1"));
	MeshComponent1->SetCollisionResponseToAllChannels(ECR_Overlap);
	WSwitcher_217_ssyl = 0;
}

// Called when the game starts or when spawned
void AZBossElementBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AZBossElementBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AZBossElementBase::SetFirstElementType_Implementation()
{
	MeshComponent1->OnComponentBeginOverlap.AddDynamic(this, &AZBossElementBase::HendleBeginOverlap);
}

void AZBossElementBase::HendleBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	                                       AActor* OtherActor,
	                                       UPrimitiveComponent* OtherComp,
	                                       int32 OtherBodyIndex,
	                                       bool bfromSweep,
	                                       const FHitResult & SweepResult)
{
	if (IsValid(SnakeOwner)) //проверим валидность указателя на змейку
	{
		SnakeOwner->ZmeykaElementOverlap(this, OtherActor);
	}
}

void AZBossElementBase::ToggleCollision()
{
	if (MeshComponent1->GetCollisionEnabled() == ECollisionEnabled::NoCollision) //текущий вид включения
	{
		MeshComponent1->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		MeshComponent1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AZBossElementBase::Interact(AActor * Interactor, bool bIsHead)
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
		SnakeOwner->Destroy();
		Snake->Destroy();
	}
}
