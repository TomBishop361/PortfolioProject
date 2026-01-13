// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


class UECSManager;
struct PORTFOLIOPROJECT_API ISystemInterface
{
	
public:
	virtual ~ISystemInterface() = default;
	virtual void Perform(UECSManager* ECS) = 0; //Pure Virtual
};
