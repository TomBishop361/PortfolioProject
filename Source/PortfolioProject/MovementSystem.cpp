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

				FVector playerPos = transformLink->LinkedActor->GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
				//Entity (Position - TargetPosition).Normalised
				// Delta normalised vector ^
				FVector CurrentPos (Position.x, Position.y, Position.z);
				
				
				

				FVector Delta ((playerPos- CurrentPos).GetSafeNormal());

				FHitResult Hit;				
				
				transformLink->LinkedActor->AddActorWorldOffset(Delta,true,&Hit);

				FVector ActualLocation = transformLink->LinkedActor->GetActorLocation();
				Position.x = ActualLocation.X;
				Position.y = ActualLocation.Y;
				Position.z = ActualLocation.Z;
			}
		}
	}
}
