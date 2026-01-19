// Fill out your copyright notice in the Description page of Project Settings.


#include "ECSManager.h"

EntityID UECSManager::CreateEntity() {
	EntityID newID = nextEntityID++;
    activeEntityCount++;
	ActiveEntities.Add(newID);
	return newID;
}

void UECSManager::DestroyEntity(EntityID entity)
{
	ActiveEntities.Remove(entity);
    activeEntityCount--;
}

bool UECSManager::isEntityValid(EntityID entity) const
{
	return ActiveEntities.Contains(entity);
}

void UECSManager::removeAllComponentsFromEntity(EntityID entity)
{
	TArray<FName> ToRemove;

	for (auto It = ComponentStorage.CreateConstIterator(); It; ++It) {
		It.Value()->RemoveEntity(entity);

		if (It.Value()->IsEmpty()) {
			ToRemove.Add(It.Key());
		}
	}
	for (const FName& Key : ToRemove)
	{
		ComponentStorage.Remove(Key);
	}
}

void UECSManager::processDestructionRequests()
{
    // Check to see if TransfromLinkComp has Map
    if (auto transformMap = GetComponentMap<FTransformLinkComponent>()) {
        for (EntityID id : entityPendingDestruction) {
            //If component for Entity Exits & is Valid Mark Actor 
            if (FTransformLinkComponent* link = transformMap->Find(id)) {
                if (IsValid(link->LinkedActor)) {
                    pendingActorDestroys.Add(link->LinkedActor);
                }
                else {
                    // LinkComp exists, but no linked actor, remove entity immediately
                    removeAllComponentsFromEntity(id);
                    DestroyEntity(id);
                }
            }
            else {
                // No transform link comp. remove entity
                removeAllComponentsFromEntity(id);
                DestroyEntity(id);
            }
        }
    }
    else {
        // No transform map. remove ALL entities
        for (EntityID id : entityPendingDestruction) {
            removeAllComponentsFromEntity(id);
            DestroyEntity(id);
        }
    }
    
    entityPendingDestruction.Empty();

    //destroy the marked actors 
    for (TWeakObjectPtr<AActor> ActorPtr : pendingActorDestroys) {
        if (ActorPtr.IsValid()) {            
            ActorPtr->Destroy();            
        }
    }
    pendingActorDestroys.Empty();
}

void UECSManager::Initialize(FSubsystemCollectionBase& Collection)
{
	ECSWorld.Systems.Add(MakeUnique<FHealthSystem>());
	ECSWorld.Systems.Add(MakeUnique<FMovementSystem>());
}

void UECSManager::Tick() {	
	for (const TUniquePtr<ISystemInterface>& System : ECSWorld.Systems)
	{
		if (System) // safety check
		{
			System->Perform(this);
		}		
	}	
    processDestructionRequests();
}
