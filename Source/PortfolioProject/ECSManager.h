// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SystemInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HealthSystem.h"
#include "MovementSystem.h"
#include "ECSManager.generated.h"


using EntityID = uint32;
UCLASS()
class PORTFOLIOPROJECT_API UECSManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	
	TArray<TUniquePtr<ISystemInterface>> Systems;
	TUniquePtr<FHealthSystem> healthSyst = MakeUnique<FHealthSystem>();
	TUniquePtr<FMovementSystem> moveSyst = MakeUnique<FMovementSystem>();

	void Tick();

	EntityID CreateEntity();
	void DestroyEntity(EntityID entity);
	bool isEntityValid(EntityID entity) const;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	template<typename T>
	TSharedPtr<TMap<EntityID, T>> GetComponentMap()
	{
		FName typeName = FName(typeid(T).name());

		if (!ComponentStorage.Contains(typeName))
		{
			return nullptr; // no components of this type exist
		}

		return StaticCastSharedPtr<TMap<EntityID, T>>(ComponentStorage[typeName]);
	}

	template<typename T>
	void AddComponent(EntityID entity, const T& component) {

		if (!isEntityValid(entity)) {
			return;
		}

		FName TypeName = FName(typeid(T).name());

		UE_LOG(LogTemp, Warning, TEXT("Value %s"), *TypeName.ToString());
		TSharedPtr<TMap<EntityID, T>> TypedStorage;

		if (ComponentStorage.Contains(TypeName)) {
			//TypedStorage = already existing sharedpointer
			TypedStorage = StaticCastSharedPtr<TMap<EntityID, T>>(ComponentStorage[TypeName]);
		}
		else {
			//Create new shared pointer and Add to ComponentStorage
			TypedStorage = MakeShared<TMap<EntityID, T>>();
			ComponentStorage.Add(TypeName, TypedStorage);
		}
		//Dereference shared pointer to access map object
		(*TypedStorage).Add(entity, component);
		UE_LOG(LogTemp, Warning, TEXT("ComponentStorage is empty: %d"), ComponentStorage.IsEmpty() ? 1 : 0);
	}

	template<typename T>
	T* GetComponent(EntityID Entity) {
		FName TypeName = FName(typeid(T).name());

		if (!ComponentStorage.Contains(TypeName)) {
			return;
		}

		auto TypedStorage = StaticCastSharedPtr<TMap<EntityID, T>>(ComponentStorage[TypeName]);
		UE_LOG(LogTemp, Warning, TEXT("ComponentStorage is empty: %d"), TypedStorage);
		return TypedStorage;

	}

	TMap<FName, TSharedPtr<void>> ComponentStorage;

private:
	EntityID nextEntityID = 0;
	TSet<EntityID> ActiveEntities;
};

