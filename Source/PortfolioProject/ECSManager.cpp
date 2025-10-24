// Fill out your copyright notice in the Description page of Project Settings.


#include "ECSManager.h"

EntityID UECSManager::CreateEntity() {
	EntityID newID = nextEntityID++;
	ActiveEntities.Add(newID);
	return newID;
}

void UECSManager::DestroyEntity(EntityID entity)
{
	ActiveEntities.Remove(entity);
}

bool UECSManager::isEntityValid(EntityID entity) const
{
	return ActiveEntities.Contains(entity);
}


template<typename T>
void UECSManager::AddComponent(EntityID entity, const T& component) {
	UE_LOG(LogTemp, Warning, TEXT("ComponentStorage is empty: %d"), ComponentStorage.IsEmpty() ? 1 : 0);
	if (!isEntityValid(entity)) {
		return;
	}

	FName TypeName = FName(typeid(T).name());

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
T* UECSManager::GetComponent(EntityID Entity) {
	FName TypeName = FName(typeid(T).name());

	if (!ComponentStorage.Contains(TypeName)) {
		return;
	}

	auto TypedStorage = StaticCastSharedPtr<TMap<EntityID, T>>(ComponentStorage[TypeName]);
	UE_LOG(LogTemp, Warning, TEXT("ComponentStorage is empty: %d"), TypedStorage);
	return TypedStorage;

}