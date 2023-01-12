// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

class AMyActor;
class AZmeyBoss;

/**
 * 
 */
UCLASS()
class ZMEYKAGAME_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual bool Initialize();
	
	UPROPERTY(meta = (BindWidget)) // meta = (BindWidget) - макрос который свяжет С++-кнопку с дочерним BP-классом
	class UButton* StartGame;
	UPROPERTY(meta = (BindWidget))
	class UButton* VykhodGame;
	UPROPERTY(meta = (BindWidget))
	class UButton* MenuGame;
	UPROPERTY(meta = (BindWidget))
	class UButton* MenuGame_1;

	UPROPERTY()
	AMyActor* MyActorActor;
	UPROPERTY()
	AZmeyBoss* ZmeyBossActor;

	UFUNCTION()
	void StartButtonClicked();
	UFUNCTION()
	void VykhodButtonClicked();
	UFUNCTION()
	void MenuButtonClicked();
	UFUNCTION()
	void MenuButtonClicked1();
public:
	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher_217;

	void vkl_tret_swit();
};