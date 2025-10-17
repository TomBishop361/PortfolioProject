// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EntityBase.generated.h"



UCLASS()
class PORTFOLIOPROJECT_API AEntityBase : public AActor
{
	GENERATED_BODY()
	
public:	
	
	
	
	// Sets default values for this actor's properties
	AEntityBase();	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int eID;
	


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
