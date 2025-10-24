// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ECSManager.h"
#include "CoreMinimal.h"
#include "HealthSystem.generated.h"


/**
 * 
 */
UCLASS()
class PORTFOLIOPROJECT_API UHealthSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UECSManager* ECS;
	
	void AdjustHealth(EntityID e, UECSManager* ecs , int healthChange);

};
