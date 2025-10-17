// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ComponentStructBase.h"
#include "HealthComponent.generated.h"



USTRUCT(BlueprintType)
struct FHealthComponent : public FComponentStructBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentHealth;

};
