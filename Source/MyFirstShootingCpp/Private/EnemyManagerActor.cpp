// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManagerActor.h"
#include <Components/ArrowComponent.h>
#include "EnemyActor.h"

// Sets default values
AEnemyManagerActor::AEnemyManagerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	spawnArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("spawnArrow"));
	spawnArrow->SetRelativeRotation(FRotator(-90, 0, 0));  //Relative �� '�θ�κ��� ������' �̶�� �ǹ�.

}

// Called when the game starts or when spawned
void AEnemyManagerActor::BeginPlay()
{
	Super::BeginPlay();

	//Timer ����
	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &AEnemyManagerActor::MakeEnemy, makeTime, true);  //GetWorldTimerManager().SetTimer(timerHandle, this, &AEnemyManagerActor::MakeEnemy, makeTime, true); �� �ۼ��ص� �ȴ�.
	
}

// Called every frame
void AEnemyManagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	/*
	//1.�ð��� �帣�ٰ�
	currentTime += DeltaTime;
	
	//2. ����, ����ð��� �����ð��� �ʰ��ϸ�(����ð� > �����ð�)
	if (currentTime > makeTime)
	{
		//3. �� ���忡�� ���� ���� spawnArrow��ġ�� ��ġ�ϰ� �ʹ�.
		GetWorld()->SpawnActor<AEnemyActor>(enemyFactory, spawnArrow->GetComponentTransform());

		//4. ���� �ð��� �ʱ�ȭ �ϰ��ʹ�.
		currentTime = 0;
	}
	*/
}

void AEnemyManagerActor::MakeEnemy()
{
	GetWorld()->SpawnActor<AEnemyActor>(enemyFactory, spawnArrow->GetComponentTransform());
}