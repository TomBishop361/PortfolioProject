// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthSystem.h"
#include "ECSManager.h"



void FHealthSystem::adjustHealth(UECSManager* ECS)
{
	if (auto DamageRequestMap = ECS->GetComponentMap<FDamageRequestComponent>()) {
		if (auto healthMap = ECS->GetComponentMap<FHealthComponent>()) {

		}
	}
}
