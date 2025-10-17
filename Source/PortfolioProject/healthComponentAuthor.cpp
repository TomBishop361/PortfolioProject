// Fill out your copyright notice in the Description page of Project Settings.


#include "healthComponentAuthor.h"




void UhealthComponentAuthor::AddToEntity(EntityID entity, UECSManager* ecs)
{
	
	ecs->AddComponent<FHealthComponent>(entity, HealthData);
}
