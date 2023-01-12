// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "MyActor.h"
#include "ZmeykaElementBase.h"
#include "Sharikunichtozhitel.generated.h"

UENUM()
enum class EMovementDirection1
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

UCLASS()
class ZMEYKAGAME_API ASharikunichtozhitel : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASharikunichtozhitel();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float MovementSpeed1;

	UPROPERTY(EditDefaultsOnly)
	float ElementSize1;

	UPROPERTY()
	EMovementDirection1 LastMoveDirection1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AActor* Interactor, bool bIsHead) override;

	UFUNCTION(BlueprintCallable)
	void Move1(float DeltaTime);
};
