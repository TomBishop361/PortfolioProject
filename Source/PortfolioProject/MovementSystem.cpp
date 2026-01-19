// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementSystem.h"


void FMovementSystem::Perform(UECSManager* ECS) {
	if (auto positionCompMap = ECS->GetComponentMap<FPositionComponent>()) {
		if (auto transformMap = ECS->GetComponentMap<FTransformLinkComponent>()){
			for (auto& [targetID, Position] : *positionCompMap) {
				FTransformLinkComponent* transformLink = transformMap->Find(targetID);

				if (!transformLink || !transformLink->LinkedActor || !transformLink->LinkedActor->IsA(AActor::StaticClass()))
				{
					continue;
				}

				
				UWorld* World = transformLink->LinkedActor->GetWorld();
				if (!World)	continue;				
				APlayerController* PC = World->GetFirstPlayerController();
				if (!PC) continue;				
				APawn* Pawn = PC->GetPawn();
				if (!Pawn) continue;
				FVector playerPos = Pawn->GetActorLocation();
				
				
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
