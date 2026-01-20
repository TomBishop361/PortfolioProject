// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthSystem.h"
#include "ECSManager.h"



void FHealthSystem::Perform(UECSManager* ECS)
{	
	if (auto DamageRequestMap = ECS->GetComponentMap<FDamageRequestComponent>()) {		
		if (auto healthMap = ECS->GetComponentMap<FHealthComponent>()) {			
			for (auto [targetID , Request] : *DamageRequestMap) {
				if (FHealthComponent* targetHealthComp = healthMap->Find(targetID))
				{	
					targetHealthComp->CurrentHealth += Request.Damage;
					targetHealthComp->CurrentHealth = FMath::Clamp(targetHealthComp->CurrentHealth, 0, targetHealthComp->MaxHealth);
					UE_LOG(LogTemp, Warning, TEXT("Remaining Health %d"), targetHealthComp->CurrentHealth);
					//Marks Damage Component for removal
					ToRemove.Add(targetID);
					if (targetHealthComp->CurrentHealth <= 0) {
						ECS->entityPendingDestruction.Add(targetID);
					}
				}
			}
		}
	}
	for (EntityID ID : ToRemove) {
		ECS->RemoveComponent<FDamageRequestComponent>(ID);
	}	
	ToRemove.Empty();	
}
