// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "BonusUskoreniye.generated.h"

class AFood;

UCLASS()
class ZMEYKAGAME_API ABonusUskoreniye : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABonusUskoreniye();

	UPROPERTY(BlueprintReadWrite)
	AFood* FoodActor1;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFood> FoodActorClass1;

private:
	FTimerHandle _loopTimerHandle1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AActor* Interactor, bool bIsHead) override;
};
