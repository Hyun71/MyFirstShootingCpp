// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyZoneActor.h"
#include <Components/BoxComponent.h>

// Sets default values
ADestroyZoneActor::ADestroyZoneActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	
	boxComp->SetBoxExtent(FVector(50, 5000, 50));
	boxComp->SetGenerateOverlapEvents(true);
	boxComp->SetCollisionProfileName(TEXT("DestroyZone"));

	SetRootComponent(boxComp);

}

// Called when the game starts or when spawned
void ADestroyZoneActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestroyZoneActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestroyZoneActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//상대(OtherActor)를 파괴하고 싶다.
	OtherActor->Destroy();
}

