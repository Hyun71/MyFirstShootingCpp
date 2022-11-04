// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManagerActor.h"
#include <Components/ArrowComponent.h>
#include "EnemyActor.h"
#include <Kismet/GameplayStatics.h>
#include "PlayerPawn.h"

// Sets default values
AEnemyManagerActor::AEnemyManagerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	spawnArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("spawnArrow"));
	spawnArrow->SetRelativeRotation(FRotator(-90, 0, 0));  //Relative 는 '부모로부터 떨어진' 이라는 의미.

}

// Called when the game starts or when spawned
void AEnemyManagerActor::BeginPlay()
{
	Super::BeginPlay();

	//Timer 구현
	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &AEnemyManagerActor::MakeEnemy, makeTime, true);  //GetWorldTimerManager().SetTimer(timerHandle, this, &AEnemyManagerActor::MakeEnemy, makeTime, true); 로 작성해도 된다.
	
}

// Called every frame
void AEnemyManagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	/*
	//1.시간이 흐르다가
	currentTime += DeltaTime;
	
	//2. 만약, 현재시간이 생성시간을 초과하면(현재시간 > 생성시간)
	if (currentTime > makeTime)
	{
		//3. 적 공장에서 적을 만들어서 spawnArrow위치에 배치하고 싶다.
		GetWorld()->SpawnActor<AEnemyActor>(enemyFactory, spawnArrow->GetComponentTransform());

		//4. 현재 시간을 초기화 하고싶다.
		currentTime = 0;
	}
	*/
}

void AEnemyManagerActor::MakeEnemy()
{
	//만약 PlayerPawn이 파괴도지 않았다면
	//만약 PlayerPawn이 nullptr이 아니라면
	/*
	AActor* target = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerPawn::StaticClass());

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerPawn::StaticClass(), OutActors);

	for each (AActor * var in OutActors)  //여기서 var는 variable이다.
	{

	}
	*/

	auto target = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (target != nullptr)
	{
		GetWorld()->SpawnActor<AEnemyActor>(enemyFactory, spawnArrow->GetComponentTransform());
	}
	
}
