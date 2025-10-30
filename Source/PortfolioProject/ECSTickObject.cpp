 // Fill out your copyright notice in the Description page of Project Settings.


#include "ECSTickObject.h"

// Sets default values
AECSTickObject::AECSTickObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AECSTickObject::BeginPlay()
{
	Super::BeginPlay();
	if (UGameInstance* GameInstance = GetGameInstance()) {
		ECS = GameInstance->GetSubsystem<UECSManager>();	
		
	}

}

// Called every frame
void AECSTickObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ECS->Tick();

}

