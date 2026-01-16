// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageRequestComponent.generated.h"
using EntityID = uint32;
/**
 * 
 */
USTRUCT()
struct PORTFOLIOPROJECT_API FDamageRequestComponent
{
	GENERATED_BODY()
public:
	//EntityID AttackerID;
	EntityID TargetID;
	int Damage;
};
