// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Food.generated.h"

class AFood;
class ABonusUskoreniye;

UCLASS()
class ZMEYKAGAME_API AFood : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFood();

	UPROPERTY(BlueprintReadWrite)
	AFood* FoodActor;

	UPROPERTY(BlueprintReadWrite)
	ABonusUskoreniye* BonusActor;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFood> FoodActorClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABonusUskoreniye> BonusActorClass;

	FVector Rasp_posl_el;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AActor* Interactor, bool bIsHead) override;

	FVector Rasp_posl_el1();
};
