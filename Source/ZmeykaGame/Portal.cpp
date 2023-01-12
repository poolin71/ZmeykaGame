// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();

	int NewY = GetActorLocation().Y;
	if (NewY == 410)
	{
		FRotator newRotator = FRotator(0, 90, 0);
		SetActorRotation(newRotator);
	}
	if (NewY == -410)
	{
		FRotator newRotator = FRotator(0, 90, 0);
		SetActorRotation(newRotator);
	}
	
	GetWorld()->GetTimerManager().SetTimer(_loopTimerHandle1, this, &APortal::DestrPort, 2.f, false);
}

void APortal::DestrPort()
{
	Destroy();
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	int NewY = GetActorLocation().Y;
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, FString::FromInt(NewY));
}