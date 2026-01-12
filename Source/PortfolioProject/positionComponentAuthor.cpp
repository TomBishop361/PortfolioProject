// Fill out your copyright notice in the Description page of Project Settings.


#include "positionComponentAuthor.h"

void UPositionComponentAuthor::AddToEntity(EntityID entity, UECSManager* ecs)
{

	ecs->AddComponent<FPositionComponent>(entity, positionData );
}
