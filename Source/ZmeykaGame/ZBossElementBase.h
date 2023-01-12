// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "ZBossElementBase.generated.h"

class UStaticMeshComponent;
class AZmeyBoss;
class UMenuWidget;

UCLASS()
class ZMEYKAGAME_API AZBossElementBase : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZBossElementBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComponent1;

	UPROPERTY()
	AZmeyBoss* SnakeOwner;

	UPROPERTY()
	UMenuWidget* MenuWidgetWidget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)
	void SetFirstElementType();
	void SetFirstElementType_Implementation();

	UFUNCTION()
	void HendleBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		                    AActor* OtherActor,
			                UPrimitiveComponent* OtherComp,
			                int32 OtherBodyIndex,
			                bool bfromSweep,
			                const FHitResult &SweepResult);

	UFUNCTION()
	void ToggleCollision();

	virtual void Interact(AActor* Interactor, bool bIsHead) override;

	class UWidgetSwitcher* WSwitcher_217_ssyl;
};
