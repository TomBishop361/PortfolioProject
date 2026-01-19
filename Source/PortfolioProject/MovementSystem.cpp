// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementSystem.h"


void FMovementSystem::Perform(UECSManager* ECS) {	
	if (!ECS) return;
	// Try to get the player pawn once per tick
	APawn* PlayerPawn = nullptr;
	if (GEngine && GEngine->GetWorldFromContextObjectChecked(ECS)->GetFirstPlayerController()) {
		APlayerController* PC = GEngine->GetWorldFromContextObjectChecked(ECS)->GetFirstPlayerController();
		if (PC) {
			PlayerPawn = PC->GetPawn();
		}
	}

	if (!PlayerPawn) {
		// No player pawn available this tick -- nothing to chase
		return;
	}

	if (auto positionCompMap = ECS->GetComponentMap<FPositionComponent>()) {
		if (auto transformMap = ECS->GetComponentMap<FTransformLinkComponent>()){
			for (auto& [targetID, Position] : *positionCompMap) {
				FTransformLinkComponent* transformLink = transformMap->Find(targetID);

				if (!transformLink)
				{
					continue;
				}

				AActor* LinkedActor = transformLink->LinkedActor;
				if (!LinkedActor || !IsValid(LinkedActor)) {
					continue;
				}
				UWorld* ActorWorld = LinkedActor->GetWorld();
				if (!ActorWorld) {
					continue;
				}

				// Use cached player pawn (ensure it's in same world)
				if (PlayerPawn->GetWorld() != ActorWorld) {
					// Different world — skip
					continue;
				}
				
				FVector playerPos = PlayerPawn->GetActorLocation();
				
				
				FVector CurrentPos (Position.x, Position.y, Position.z);
				FVector Delta ((playerPos- CurrentPos).GetSafeNormal());

				FHitResult Hit;				
				
				LinkedActor->AddActorWorldOffset(Delta, true, &Hit);

				FVector ActualLocation = transformLink->LinkedActor->GetActorLocation();
				Position.x = ActualLocation.X;
				Position.y = ActualLocation.Y;
				Position.z = ActualLocation.Z;
			}
		}
	}
}
