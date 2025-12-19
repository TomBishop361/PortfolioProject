// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "componentAuthorBase.h"
#include "positionComponentAuthor.generated.h"
/**
 *
 */
UCLASS(Blueprintable)
class PORTFOLIOPROJECT_API UPositionComponentAuthor : public UcomponentAuthorBase
{
	GENERATED_BODY()
public:
	virtual void AddToEntity(EntityID entity, UECSManager* ecs) override;
};
