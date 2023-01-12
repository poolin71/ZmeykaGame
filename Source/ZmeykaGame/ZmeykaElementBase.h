// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "ZmeykaElementBase.generated.h"

class UStaticMeshComponent;
class AMyActor;
class UMenuWidget;

UCLASS()
class ZMEYKAGAME_API AZmeykaElementBase : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZmeykaElementBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY()
	AMyActor* SnakeOwner;

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

	virtual void Interact(AActor* Interactor, bool bIsHead) override;

	UFUNCTION()
	void HendleBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bfromSweep,
			const FHitResult &SweepResult);

	UFUNCTION()
	void ToggleCollision();
};