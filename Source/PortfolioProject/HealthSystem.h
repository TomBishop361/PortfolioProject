// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SystemInterface.h"
#include "DamageRequestComponent.h"
#include "HealthComponent.h"

struct PORTFOLIOPROJECT_API FHealthSystem : public ISystemInterface
{
	
public:
	void Perform(UECSManager* ECS) override;

private:
	TArray<EntityID> ToRemove;
	TArray<EntityID> ToDestroy;
};
