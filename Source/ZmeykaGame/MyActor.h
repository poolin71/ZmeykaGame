// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "MyActor.generated.h"

class AZmeykaElementBase;
class UMenuWidget;
class AZmeyBoss;

UENUM()
enum class EMovementDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

UCLASS()
class ZMEYKAGAME_API AMyActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AZmeykaElementBase> ZmeykaElementClass;

	UPROPERTY(EditDefaultsOnly)
	float ElementSize;

	UPROPERTY()
	float MovementSpeed1;

	UPROPERTY()
	TArray<AZmeykaElementBase*> ZmeykaElements; //массив

	UPROPERTY()
	EMovementDirection LastMoveDirection;

	UPROPERTY()
	FVector NewLocation1;

	UPROPERTY()
	UMenuWidget* MenuWidgetWidget;

	UPROPERTY()
	AZmeyBoss* ZmeyBossActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void AddZmeykaElement(FVector Rasp_posl_el, int ElementsNum = 1);

	UFUNCTION(BlueprintCallable)
	void Move();

	UFUNCTION()
	void ZmeykaElementOverlap(AZmeykaElementBase* OverlappedElement, AActor* Other); //ивент - наш блок сколизился с "AActor* Other"

	virtual void Interact(AActor* Interactor, bool bIsHead) override;

	UFUNCTION()
	void GGlh(AActor* otheMy); //функция вызова из других файлов

	void MinusOne();

	void MinusTwo();

	int32 Score1 = 3, score2;
	int prop_izm_tick;
	int prop_sozd_perv_el;
};