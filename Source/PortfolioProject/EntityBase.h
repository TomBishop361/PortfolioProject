// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ECSManager.h"
#include "componentAuthorBase.h"
#include "EntityBase.generated.h"



UCLASS()
class PORTFOLIOPROJECT_API AEntityBase : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, Instanced, Category = "ECS")
	TArray<UcomponentAuthorBase*> ecsComponents;
	
	// Sets default values for this actor's properties
	AEntityBase();	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	EntityID e;
	


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
