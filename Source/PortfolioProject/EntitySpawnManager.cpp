// Fill out your copyright notice in the Description page of Project Settings.


#include "EntitySpawnManager.h"


AEntitySpawnManager::AEntitySpawnManager() {    
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
}

void AEntitySpawnManager::SpawnECSActor()
{
    RandomNumber = FMath::RandRange(0, spawnPositions.Num() - 1);
    
    if (!BlueprintActorClassEntity) return;
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.SpawnCollisionHandlingOverride =
        ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    GetWorld()->SpawnActor<AActor>(
        BlueprintActorClassEntity ,
        spawnPositions[RandomNumber],
        FRotator::ZeroRotator,
        SpawnParams
        
    );
    UE_LOG(LogTemp, Warning, TEXT("EntitySpawned"));
}

// Called when the game starts or when spawned
void AEntitySpawnManager::BeginPlay()
{
	Super::BeginPlay();
    if (UGameInstance* GameInstance = GetGameInstance()) {        
        ECS = GameInstance->GetSubsystem<UECSManager>();        
    }
    SpawnECSActor();
}

// Called every frame
void AEntitySpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);    
    if (ECS) {
        if (ECS->activeEntityCount < SpawnAmount) {            
            SpawnECSActor();
        }
    }
}

