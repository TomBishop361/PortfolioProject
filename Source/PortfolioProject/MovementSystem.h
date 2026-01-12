// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PositionComponent.h"
#include "TransformLinkComponent.h"
#include "MovementSystem.generated.h"
/**
 * 
 */
class UECSManager;
USTRUCT()
struct PORTFOLIOPROJECT_API FMovementSystem
{
	GENERATED_BODY()
public:
	void Perform(UECSManager* ECS);
};
