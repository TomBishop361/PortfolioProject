// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SystemInterface.h"
#include "ECSWorld.h"
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
	ECSWorld ECSWorld;

	void Tick();

	EntityID CreateEntity();
	void DestroyEntity(EntityID entity);
	bool isEntityValid(EntityID entity) const;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	
	

	template<typename T>
	TMap<EntityID, T>* GetComponentMap()
	{
		FName typeName = FName(typeid(T).name());

		if (!ComponentStorage.Contains(typeName))
		{
			return nullptr; // no components of this type exist
		}

		auto TypedStorage = StaticCastSharedPtr<TComponentStorage<T>>(ComponentStorage[typeName]);
		return &TypedStorage->Data;
	}

	template<typename T>
	void AddComponent(EntityID entity, const T& component) {


		FName TypeName = FName(typeid(T).name());

		UE_LOG(LogTemp, Warning, TEXT("Value %s"), *TypeName.ToString());
		TSharedPtr<TComponentStorage<T>> TypedStorage;

		if (ComponentStorage.Contains(TypeName)) {
			//TypedStorage = already existing sharedpointer
			TypedStorage = StaticCastSharedPtr<TComponentStorage<T>>(ComponentStorage[TypeName]);
		}
		else {
			//Create new shared pointer and Add to ComponentStorage
			TypedStorage = MakeShared<TComponentStorage<T>>();
			ComponentStorage.Add(TypeName, TypedStorage);
		}
		//Dereference shared pointer to access map object
		TypedStorage->Data.Add(entity, component);

		UE_LOG(LogTemp, Warning, TEXT("ComponentStorage is empty: %d"), ComponentStorage.IsEmpty() ? 1 : 0);
	}

	

	struct IComponentStorage
	{
		virtual ~IComponentStorage() = default;
	};

	template<typename T>
	struct TComponentStorage : IComponentStorage
	{
		TMap<EntityID, T> Data;
	};

	TMap<FName, TSharedPtr<IComponentStorage>> ComponentStorage;

private:
	EntityID nextEntityID = 0;
	TSet<EntityID> ActiveEntities;
};

