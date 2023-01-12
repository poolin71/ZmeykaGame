// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Interactable.h"
#include "MyActor.h"
#include "Sharikunichtozhitel.h"
#include "Portal.h"
#include "GameFramework/SpringArmComponent.h"
#include "Teleport.generated.h"

UCLASS()
class ZMEYKAGAME_API ATeleport : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleport();

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<AActor> ActorToSpawn1;

private:
	FTimerHandle _loopTimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void SpawnObject(FTransform NewTransform);

	UFUNCTION()
	void SpawnObject1(FTransform NewTransform1);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AActor* Interactor, bool bIsHead) override;

	int32 Score;

	UPROPERTY(EditAnywhere, Category = "Teleporter")
	ATeleport* otheMy1;

	UPROPERTY(EditAnywhere, Category = "Teleporter")
	ATeleport* otheMy2;
};