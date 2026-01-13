// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementSystem.h"


void FMovementSystem::Perform(UECSManager* ECS) {
	if (auto positionCompMap = ECS->GetComponentMap<FPositionComponent>()) {
		if (auto transformMap = ECS->GetComponentMap<FTransformLinkComponent>()){
			for (auto& [targetID, Position] : *positionCompMap) {
				FTransformLinkComponent* transformLink = transformMap->Find(targetID);

				if (!transformLink || !transformLink->LinkedActor)
				{
					continue;
				}

				Position.x += 0.1f;
				Position.y += 0.1f;
				Position.z += 0.1f;

				FVector NewLocation(Position.x, Position.y, Position.z);
				transformLink->LinkedActor->SetActorLocation(NewLocation);
			}
		}
	}
}
