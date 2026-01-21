// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthSystem.h"
#include "ECSManager.h"



void FHealthSystem::Perform(UECSManager* ECS)
{	
	auto* damageRequestStorage = ECS->GetComponentStorage<FDamageRequestComponent>();
	auto* healthStorage = ECS->GetComponentStorage<FHealthComponent>();
	if (damageRequestStorage) {
		if (healthStorage) {
			for (int32 i = 0; i < damageRequestStorage->dense.Num(); i++) {
				//Processing all Dmg requests
				EntityID targetID = damageRequestStorage->entities[i];
				FDamageRequestComponent& Request = damageRequestStorage->dense[i];

				int32 HealthIndx = healthStorage->sparse[targetID];

				//Entity has a health component
				if (HealthIndx != INDEX_NONE) {

					FHealthComponent& targetHealth = healthStorage->dense[HealthIndx];

					targetHealth.CurrentHealth += Request.Damage;
					
					targetHealth.CurrentHealth = FMath::Clamp(targetHealth.CurrentHealth, 0, targetHealth.MaxHealth);
					UE_LOG(LogTemp, Warning, TEXT("Target ID%d"), targetID);
					UE_LOG(LogTemp, Warning, TEXT("Health %d"), targetHealth.CurrentHealth);
					//Marks Damage Component for removal
					ToRemove.Add(targetID);

					if (targetHealth.CurrentHealth <= 0)
					{
						ECS->entityPendingDestruction.Add(targetID);
					}
				}
			}
		}
	}
	for (EntityID ID : ToRemove) {		
		damageRequestStorage->RemoveEntity(ID);
	}	
	ToRemove.Empty();	
}
