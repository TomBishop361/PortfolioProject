// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <typeindex>
#include <type_traits>
#include "HealthSystem.h"


using EntityID = uint32;

/**
 * 
 */
class PORTFOLIOPROJECT_API ECSCore
{
public:
	TTuple<FHealthSystem> Systems;

	TMap<FName, TSharedPtr<void>> ComponentStorage;



	

private:
	EntityID nextEntityID = 0;
	TSet<EntityID> ActiveEntities;
};
