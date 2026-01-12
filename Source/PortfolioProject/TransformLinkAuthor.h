// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TransformLinkComponent.h"
#include "componentAuthorBase.h"
#include "transformLinkAuthor.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, EditInlineNew)
class PORTFOLIOPROJECT_API UTransformLinkAuthor : public UcomponentAuthorBase
{
	GENERATED_BODY()
public:
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransformLinkComponent transformLink;*/
	FTransformLinkComponent Link;

	
	virtual void AddToEntity(EntityID entity, UECSManager* ecs) override;
	
};
