// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ECSManager.h"
#include "EntitySpawnManager.generated.h"

UCLASS()
class PORTFOLIOPROJECT_API AEntitySpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	int32 RandomNumber;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ECS")
	TSubclassOf<AActor> BlueprintActorClassEntity;

	UPROPERTY(EditAnywhere, Category = "ECS")
	TArray<FVector> spawnPositions;

	UPROPERTY(EditAnywhere, Category = "ECS")
	int SpawnAmount = 30;

	AEntitySpawnManager();
	void SpawnECSActor();
	UECSManager* ECS;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
