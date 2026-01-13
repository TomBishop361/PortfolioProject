// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityBase.h"
#include "Engine/GameInstance.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AEntityBase::AEntityBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bCanEverTick = false;

	UCapsuleComponent* Capsule =
		CreateDefaultSubobject<UCapsuleComponent>(TEXT("RootCapsule"));

	RootComponent = Capsule;

	Capsule->InitCapsuleSize(34.f, 88.f);
	Capsule->SetCollisionProfileName(TEXT("BlockAll"));
	Capsule->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Capsule->SetSimulatePhysics(false);
	
}


// Called when the game starts or when spawned
void AEntityBase::BeginPlay()
{	
	Super::BeginPlay();
	if (UGameInstance* GameInstance = GetGameInstance()) {
		if (UECSManager* ECS = GameInstance->GetSubsystem<UECSManager>()) {
			e = ECS->CreateEntity();

			for (auto* author : ecsComponents) {
				if (author) {
					author->AddToEntity(e, ECS);
					UE_LOG(LogTemp, Warning, TEXT("Called AddToEntity"));
				}
			}
		}
	}
	
}

// Called every frame
void AEntityBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

