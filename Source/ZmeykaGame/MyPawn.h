// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

class UCameraComponent;
class AMyActor;
class AFood;
class AZmeyBoss;

UCLASS()
class ZMEYKAGAME_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

	UPROPERTY(BlueprintReadWrite)
	UCameraComponent* PawnCamera;

	UPROPERTY(BlueprintReadWrite)
	AMyActor* MyActorActor;

	UPROPERTY(BlueprintReadWrite)
	AZmeyBoss* ZmeyBossActor;

	UPROPERTY(BlueprintReadWrite)
	AFood* FoodActor;

	UPROPERTY(EditDefaultsOnly) //EditDefaultOnly
	TSubclassOf<AMyActor> MyActorActorClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AZmeyBoss> ZmeyBossActorClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AFood> FoodActorClass;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void CreateZmeykaActor();

	void CreateZBossActor();

	void CreateFood();

	UFUNCTION()
	void HandlePlayerVerticalInput(float value);
	UFUNCTION()
	void HandlePlayerHorizontalInput(float value);
};
