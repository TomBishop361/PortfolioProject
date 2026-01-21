// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SystemInterface.h"
#include "PositionComponent.h"
#include "TransformLinkComponent.h"


struct PORTFOLIOPROJECT_API FMovementSystem : public ISystemInterface
{
	class ECSManager;
public:
	void Perform(UECSManager* ECS) override;
};
