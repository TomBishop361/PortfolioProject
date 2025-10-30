// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HealthSystem.h"
#include "ECSManager.generated.h"
/**
 * 
 */
using EntityID = uint32;

UCLASS()
class PORTFOLIOPROJECT_API UECSManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	TTuple<FHealthSystem> Systems;
	
	//virtual void Tick(float DeltaTime) override;
	//virtual TStatId GetStatId() const override;
	//virtual bool IsTickable() const override;

	void Tick();

	EntityID CreateEntity();
	void DestroyEntity(EntityID entity);
	bool isEntityValid(EntityID entity) const;

	template<typename T>
	TSharedPtr<TMap<EntityID, T>> GetComponentMap();

	template<typename T>
	void AddComponent(EntityID entity, const T& component);

	template<typename T>
	T* GetComponent(EntityID entity);

	TMap<FName, TSharedPtr<void>> ComponentStorage;




private:
	EntityID nextEntityID = 0;
	TSet<EntityID> ActiveEntities;

	


};

