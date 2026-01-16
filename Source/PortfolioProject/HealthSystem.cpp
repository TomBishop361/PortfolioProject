// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthSystem.h"
#include "ECSManager.h"



void FHealthSystem::Perform(UECSManager* ECS)
{
	UE_LOG(LogTemp, Warning, TEXT("HealthSystem"));
	if (auto DamageRequestMap = ECS->GetComponentMap<FDamageRequestComponent>()) {
		if (auto healthMap = ECS->GetComponentMap<FHealthComponent>()) {
			for (auto [targetID , Request] : *DamageRequestMap) {
				FHealthComponent* targetHealthComp = healthMap->Find(targetID);
				
				targetHealthComp->CurrentHealth += Request.Damage;
				
				UE_LOG(LogTemp, Warning, TEXT("Applied Damage"));
				if (targetHealthComp->CurrentHealth <= 0) {
					//ECS->AddComponent(targetID,FDeathComponent);


				}
			}
		}
	}
}
