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
					ToRemove.Add(targetID);

					if (targetHealthComp->CurrentHealth <= 0) {
						//ECS->AddComponent(targetID,FDeathComponent);


					}
				}
			}
		}
	}
	for(EntityID ID : ToRemove) ECS->RemoveComponent<FDamageRequestComponent>(ID);
}
