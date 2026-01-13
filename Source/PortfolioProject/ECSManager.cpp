// Fill out your copyright notice in the Description page of Project Settings.


#include "ECSManager.h"

EntityID UECSManager::CreateEntity() {
	EntityID newID = nextEntityID++;
	ActiveEntities.Add(newID);
	return newID;
}

void UECSManager::DestroyEntity(EntityID entity)
{
	ActiveEntities.Remove(entity);
}

bool UECSManager::isEntityValid(EntityID entity) const
{
	return ActiveEntities.Contains(entity);
}

void UECSManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Systems.Add(MakeUnique<FMovementSystem>());
}

void UECSManager::Tick() {
	for (const TUniquePtr<ISystemInterface>& System : Systems)
	{
		if (System) // safety check
		{
			System->Perform(this);
		}
	}
	
}








