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
					UE_LOG(LogTemp, Warning, TEXT("DamageRequestSeen"));
					targetHealthComp->CurrentHealth += Request.Damage;
					targetHealthComp->CurrentHealth = FMath::Clamp(targetHealthComp->CurrentHealth, 0, targetHealthComp->MaxHealth);
					//Marks Damage Component for removal
					ToRemove.Add(targetID);
					if (targetHealthComp->CurrentHealth <= 0) {
						ToDestroy.Add(targetID);
					}
				}
			}
		}
	}
	for (EntityID ID : ToRemove) {
		ECS->RemoveComponent<FDamageRequestComponent>(ID);
	}
	for (EntityID ID : ToDestory) {

	}
	ToRemove.Empty();
	ToDestroy.Empty();
}
