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
	if (ECS->ComponentStorage.Contains("DamageRequestComponent")) {
		auto* ptr = ECS->ComponentStorage.Find("DamageRequestComponent");
		//cast
		auto DamageRequestCompMap& = StaticCast<TMap<EntityID, FDamageRequestComponent>>(*ptr);

		for (const auto& Pair : DamageRequestCompMap) {
			EntityID id = Pair.Key;
			FDamageRequestComponent component = Pair.Value;


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
