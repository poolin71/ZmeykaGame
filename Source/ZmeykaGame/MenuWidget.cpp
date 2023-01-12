// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuWidget.h"
#include "Components/Button.h"
#include "MyActor.h"
#include "Kismet/GameplayStatics.h"
#include "ZmeyBoss.h"
#include "Components/WidgetSwitcher.h"
#include "Blueprint/UserWidget.h"

bool UMenuWidget::Initialize()
{
	Super::Initialize();
	MyActorActor = 0;
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyActor::StaticClass(), FoundActors);
	for (AActor* TActor : FoundActors)
	{
		AMyActor* MyActor = Cast<AMyActor>(TActor);
		if (MyActor != nullptr)
		{
			MyActorActor = MyActor;
		}
	}
	WidgetSwitcher_217->SetActiveWidgetIndex(1);
	StartGame->OnClicked.AddDynamic(this, &UMenuWidget::StartButtonClicked);
	VykhodGame->OnClicked.AddDynamic(this, &UMenuWidget::VykhodButtonClicked);
	MenuGame->OnClicked.AddDynamic(this, &UMenuWidget::MenuButtonClicked);
	MenuGame_1->OnClicked.AddDynamic(this, &UMenuWidget::MenuButtonClicked1);
	return false;
}

void UMenuWidget::StartButtonClicked()
{
	WidgetSwitcher_217->SetActiveWidgetIndex(0);
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
	MyActorActor->prop_izm_tick = 1;
	ZmeyBossActor->prop_izm_tick = 1;
	/*RemoveFromParent();*/
}

void UMenuWidget::VykhodButtonClicked()
{
	FGenericPlatformMisc::RequestExit(false);
}

void UMenuWidget::MenuButtonClicked()
{
	MyActorActor->score2 = 0;
	UGameplayStatics::OpenLevel(this, "Main");
}

void UMenuWidget::MenuButtonClicked1()
{
	MyActorActor->score2 = 0;
	UGameplayStatics::OpenLevel(this, "Main");
}

void UMenuWidget::vkl_tret_swit()
{
	WidgetSwitcher_217->SetActiveWidgetIndex(2);
	ZmeyBossActor->Destroy();
}