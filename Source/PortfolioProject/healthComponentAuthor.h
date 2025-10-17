// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "componentAuthorBase.h"
#include "healthComponentAuthor.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PORTFOLIOPROJECT_API UhealthComponentAuthor : public UcomponentAuthorBase
{
	GENERATED_BODY()

public:
	FHealthComponent HealthData;
	
	virtual void AddToEntity(EntityID entity, UECSManager* ecs) override;

private:	
	
};
