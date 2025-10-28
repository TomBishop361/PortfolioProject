// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthSystem.h"


bool isInitialised = false;

void UHealthSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	if (UGameInstance* GameInstance = GetGameInstance()) {
		if (GameInstance->GetSubsystem<UECSManager>()) {
			ECS = GameInstance->GetSubsystem<UECSManager>();
			isInitialised = true;

			
		}
	}
}

void UHealthSystem::Tick(float DeltaTime)
{
	if (!isInitialised) {
		UE_LOG(LogTemp, Warning, TEXT("ECS is null in UHealthSystem::Tick"));
		return;
	}
	static const FName DamageCompName("FDamageRequestComponent");
	static const FName HealthCompName("FHealthComponent");


	if (auto* DamageRequestMap = ECS->GetComponentMap<FDamageRequestComponent>()) {
		if (auto* HealthCompMap = ECS->GetComponentMap<FHealthComponent>()) {

			for (auto& pair : *DamageRequestMap) {
				EntityID Entity = pair.Key;
				FDamageRequestComponent& DamageReqComp = pair.Value;

				EntityID Target = DamageReqComp.TargetID;
				int Damage = DamageReqComp.Damage;

				if (!HealthCompMap->Contains(Target)) {

					continue;
				}

				if (FHealthComponent* TargetHealth = HealthCompMap->Find(Target)) {
					TargetHealth->CurrentHealth -= Damage;
					if (TargetHealth->CurrentHealth <= 0) {
						//ToImplement
						//ECS->AddComponent(Target, FDeathComponent{});
					}

				}

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
