// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SystemInterface.h"
/**
 * 
 */

//Prevents Unreal GC
struct PORTFOLIOPROJECT_API ECSWorld
{
	TArray<TUniquePtr<ISystemInterface>> Systems;
	
};
