// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "healthComponentAuthor.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PORTFOLIOPROJECT_API UhealthComponentAuthor : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "ECSComponent")
	void AuthorComponent(int e, FHealthComponent healthComponent);

private:	
	
};
