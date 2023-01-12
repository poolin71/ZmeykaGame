// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "TimerManager.h"
#include "ZmeyBoss.generated.h"

class AZBossElementBase;

UENUM()
enum class EMovementDirection2
{
	UP2,
	DOWN2,
	LEFT2,
	RIGHT2
};

UCLASS()
class ZMEYKAGAME_API AZmeyBoss : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZmeyBoss();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AZBossElementBase> ZBossElementClass;

	UPROPERTY(EditDefaultsOnly)
	float ElementSize1;

	UPROPERTY()
	TArray<AZBossElementBase*> ZBossElements; //массив

	UPROPERTY()
	EMovementDirection2 LastMoveDirection2;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float MovementSpeed2;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void AddZBossElement(int ElementsNum1 = 1);

	UFUNCTION(BlueprintCallable)
	void Move2();

	void RandNaprav();

	UFUNCTION()
	void GGlh1(AActor* otheMy1); //функция вызова из других файлов

	UFUNCTION()
	void ZmeykaElementOverlap(AZBossElementBase* OverlappedElement, AActor* Other); //ивент - наш блок сколизился с "AActor* Other"

	int prop_izm_tick;
};
