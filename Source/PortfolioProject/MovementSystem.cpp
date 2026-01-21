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

	auto* positionStorage = ECS->GetComponentStorage<FPositionComponent>();
	auto* transformStorage = ECS->GetComponentStorage<FTransformLinkComponent>();
	if (positionStorage) {
		if (transformStorage){
			for (int32 i = 0; i < transformStorage->dense.Num(); i++) {

				EntityID targetID = positionStorage->entities[i];
				FPositionComponent& entityPositionComp = positionStorage->dense[i];

				int32 transformIndx = transformStorage->sparse[targetID];

				if (transformIndx != INDEX_NONE) {

					FTransformLinkComponent& transformLink = transformStorage->dense[transformIndx];
					

					AActor* LinkedActor = transformLink.LinkedActor;
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


					FVector CurrentPos(entityPositionComp.x, entityPositionComp.y, entityPositionComp.z);
					FVector Delta((playerPos - CurrentPos).GetSafeNormal());

					FHitResult Hit;

					LinkedActor->AddActorWorldOffset(Delta, true, &Hit);

					FVector ActualLocation = transformLink.LinkedActor->GetActorLocation();
					entityPositionComp.x = ActualLocation.X;
					entityPositionComp.y = ActualLocation.Y;
					entityPositionComp.z = ActualLocation.Z;
				}
			}
			}
		}
}
