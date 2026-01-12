// Fill out your copyright notice in the Description page of Project Settings.


#include "TransformLinkAuthor.h"


void UTransformLinkAuthor::AddToEntity(EntityID entity, UECSManager* ecs)
{
	
	if (AActor* ownerActor = Cast<AActor>(GetOuter()))
	{
		Link.LinkedActor = ownerActor;
	}

	ecs->AddComponent<FTransformLinkComponent>(entity, Link);
}
