// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ECSManager.h"	
#include "componentAuthorBase.generated.h"

/**
 * 
 */
UCLASS(Abstract,Blueprintable,EditInlineNew,DefaultToInstanced)
class PORTFOLIOPROJECT_API UcomponentAuthorBase : public UObject
{
	GENERATED_BODY()
public:
	
	virtual void AddToEntity(EntityID entity, UECSManager* ecs) PURE_VIRTUAL(UcomponentAuthorBase::AddToEntity, );
};
