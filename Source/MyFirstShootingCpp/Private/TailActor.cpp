// Fill out your copyright notice in the Description page of Project Settings.


#include "TailActor.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ATailActor::ATailActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATailActor::BeginPlay()
{
	Super::BeginPlay();

	//태어날때 만약 target이 nullptr이라면 BP_PlayerPawn을 찾아서 목적지로 삼고 싶다.
	if (target == nullptr) { // ! → 반전 시킨다는 의미.
		target = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	}
}

// Called every frame
void ATailActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//살아가면서 목적지를 향하는 방향을 구하고 이동하고 싶다.
	FVector dir = target->GetActorLocation() - GetActorLocation();  //this생략 가능.
	dir.Normalize();
	SetActorLocation(GetActorLocation() + dir * speed * DeltaTime);
}

