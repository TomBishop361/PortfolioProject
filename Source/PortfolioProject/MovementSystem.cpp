// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementSystem.h"


void FMovementSystem(UECSManager* ECS) {
	if (auto positionCompMap = ECS->GetComponentMap<FPositionComponent>()) {
		if (auto transformMap = ECS->GetComponentMap<FTransformLinkComponent>()){
			for (auto [targetID, Position] : *positionCompMap) {
				FTransformLinkComponent* transformLink = transformMap->Find(targetID);

				Position.x += 0.1f;
				Position.y += 0.1f;
				Position.z += 0.1f;

				FTransform transform = transformLink->LinkedActor->GetActorTransform();

				
			}
		}
	}
}
