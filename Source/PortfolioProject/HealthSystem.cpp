// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthSystem.h"




void UHealthSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	if (UGameInstance* GameInstance = GetGameInstance()) {
		if (GameInstance->GetSubsystem<UECSManager>()) {
			ECS = GameInstance->GetSubsystem<UECSManager>();
		}
	}
}

void UHealthSystem::Tick(float DeltaTime)
{
	if (ECS->ComponentStorage.Contains("FDamageRequestComponent") && ECS->ComponentStorage.Contains("FHealthComponent")) {
		TSharedPtr<TMap<EntityID, FDamageRequestComponent>> DamageRequestMap;
		TSharedPtr<TMap<EntityID, FHealthComponent>> HealthCompMap;

		DamageRequestMap = StaticCastSharedPtr<TMap<EntityID, FDamageRequestComponent>>(ECS->ComponentStorage[FName("FDamageRequestComponent")]);
		HealthCompMap = StaticCastSharedPtr<TMap<EntityID, FHealthComponent>>(ECS->ComponentStorage[FName("FHealthComponent")]);
		
		for (auto& pair : *DamageRequestMap) {
			EntityID Entity = pair.Key;
			FDamageRequestComponent& DamageReqComp = pair.Value;

			EntityID Target = DamageReqComp.TargetID;
			int Damage = DamageReqComp.Damage;

			if (!HealthCompMap->Contains(Target))
				continue;

			if (FHealthComponent* TargetHealth = HealthCompMap->Find(Target)) {
				TargetHealth->CurrentHealth -= Damage;
			}

		}
	}

}

TStatId UHealthSystem::GetStatId() const
{
	return TStatId();
}

bool UHealthSystem::IsTickable() const
{
	return true;
}

void UHealthSystem::AdjustHealth(EntityID e, UECSManager* ecs, int healthChange)
{

}
