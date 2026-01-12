// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TransformLinkComponent.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct PORTFOLIOPROJECT_API FTransformLinkComponent
{
	GENERATED_BODY()
	
public:
	

	UPROPERTY()
	AActor* LinkedActor = nullptr;
};
