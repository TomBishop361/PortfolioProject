// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "ECSManager.h"
#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "DamageRequestComponent.h"
#include "HealthSystem.generated.h"


/**
 * 
 */
UCLASS()
class PORTFOLIOPROJECT_API UHealthSystem : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()
public:
	UECSManager* ECS;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	virtual void Tick(float DeltaTime) override;

	virtual TStatId GetStatId() const override;

	virtual bool IsTickable() const override;

	void AdjustHealth(EntityID e, UECSManager* ecs , int healthChange);

};
