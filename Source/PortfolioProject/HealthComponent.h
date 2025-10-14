// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct FHealthComponent
{
	GENERATED_BODY()

public:
	int MaxHealth;
	int CurrentHealth;

	

};
