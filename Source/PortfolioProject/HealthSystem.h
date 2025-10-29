// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageRequestComponent.h"
#include "HealthSystem.generated.h"

/**
 * 
 */

class UECSManager;
USTRUCT()
struct PORTFOLIOPROJECT_API FHealthSystem
{
	GENERATED_BODY()
public:
	void adjustHealth(UECSManager* ECS);
};
