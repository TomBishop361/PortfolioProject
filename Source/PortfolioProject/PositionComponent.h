// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PositionComponent.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct PORTFOLIOPROJECT_API FPositionComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float x;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float y;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float z;
};
