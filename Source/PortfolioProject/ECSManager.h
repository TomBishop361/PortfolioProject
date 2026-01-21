// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SystemInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HealthSystem.h"
#include "ComponentTypeID.h"
#include "MovementSystem.h"
#include "ECSManager.generated.h"


using EntityID = int32;
UCLASS()
class PORTFOLIOPROJECT_API UECSManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	//Wrapped to keep outside the GC’s reach.
	struct ECSWorld
	{
		TArray<TUniquePtr<ISystemInterface>> Systems;

	};
	ECSWorld ECSWorld;
	TArray<EntityID> entityPendingDestruction;
	TArray<AActor*> pendingActorDestroys;
	int activeEntityCount = 0;
	void Tick();

	EntityID CreateEntity();
	void DestroyEntity(EntityID entity);
	bool isEntityValid(EntityID entity) const;
	void removeAllComponentsFromEntity(EntityID entity);
	void processDestructionRequests();
	

	struct IComponentStorage
	{
		virtual ~IComponentStorage() = default;
		//Pure Virtual
		virtual void RemoveEntity(EntityID Entity) = 0;
		virtual bool isEmpty() const = 0;
	};

	template<typename T>
	struct TComponentStorage : IComponentStorage {
		TArray<int32> sparse;
		TArray<T> dense;
		TArray<EntityID> entities;

		void AddEntity(EntityID Entity, const T& Value)
		{
			if (sparse.Num() <= Entity)
			{
				//Grows array setting new values to 0. Last 
				sparse.SetNumZeroed(Entity + 1);
			}

			//Stores Index of component in dense array
			sparse[Entity] = dense.Add(Value);
			entities.Add(Entity);
		}
		virtual void RemoveEntity(EntityID Entity) override
		{
			if (sparse.Num() > Entity && sparse[Entity] != INDEX_NONE)
			{
				//get component index
				int32 indxToRemove = sparse[Entity];

				// swaps removed entity's data with the last entry
				dense[indxToRemove] = dense.Last();
				entities[indxToRemove] = entities.Last();

				// Update sparse value new dense index
				sparse[entities[indxToRemove]] = indxToRemove;

				// Remove the last item
				dense.Pop();
				entities.Pop();

				// Mark entity as removed
				sparse[Entity] = INDEX_NONE;
			}
		}

		virtual bool isEmpty() const override
		{
			return dense.Num() == 0;
		}
	};

	TMap<int32, TSharedPtr<IComponentStorage>> ComponentStorage;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	template<typename T>
	TComponentStorage<T>* GetComponentStorage()
	{
		int32 typeName = ComponentTypeID::GetTypeID<T>();

		if (!ComponentStorage.Contains(typeName))
		{
			return nullptr; // no components of this type exist
		}

		auto TypedStorage = StaticCastSharedPtr<TComponentStorage<T>>(ComponentStorage[typeName]);
		return TypedStorage.Get();
	}

	template<typename T>
	void AddComponent(EntityID entity, const T& component) {
		int32 typeName = ComponentTypeID::GetTypeID<T>();

		//UE_LOG(LogTemp, Warning, TEXT("Value %s"), *TypeName.ToString());
		TSharedPtr<TComponentStorage<T>> TypedStorage;

		if (ComponentStorage.Contains(typeName)) {
			//TypedStorage = already existing sharedpointer
			TypedStorage = StaticCastSharedPtr<TComponentStorage<T>>(ComponentStorage[typeName]);
		}
		else {
			//Create new shared pointer and Add to ComponentStorage
			TypedStorage = MakeShared<TComponentStorage<T>>();
			ComponentStorage.Add(typeName, TypedStorage);
		}
		//Dereference shared pointer to access map object
		TypedStorage->AddEntity(entity, component);

		//UE_LOG(LogTemp, Warning, TEXT("ComponentStorage is empty: %d"), ComponentStorage.IsEmpty() ? 1 : 0);
	}
	
	template<typename T>
	void RemoveComponent(EntityID entity) {
		int32 typeName = ComponentTypeID::GetTypeID<T>();
		if (!ComponentStorage.Contains(typeName)) {
			return;
		}
		auto TypedStorage = StaticCastSharedPtr<TComponentStorage<T>>(ComponentStorage[typeName]);
		TypedStorage->RemoveEntity(entity);

		if (TypedStorage->isEmpty())
		{
			ComponentStorage.Remove(typeName);
		}
	}	


private:
	EntityID nextEntityID = 0;
	TSet<EntityID> ActiveEntities;
};

