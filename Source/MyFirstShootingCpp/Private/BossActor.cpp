// Fill out your copyright notice in the Description page of Project Settings.


#include "BossActor.h"

// Sets default values
ABossActor::ABossActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABossActor::BeginPlay()
{
	Super::BeginPlay();

	state = EBossState::Idle;
	origin = GetActorLocation();
	
}

// Called every frame
void ABossActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if문을 사용하여 원하는 상태값을 적용시킴.
	/*if (state == EBossState::Move)
	{

	}
	else if(state == EBossState::Attack)*/
	
	switch (state)
	{
	case EBossState::Move:
		TickMove();  //여기에 구현하면 너무 복잡하므로 따로 함수를 만들어서 구현한다.
		break;
	case EBossState::Attack:
		TickAttack();
		break;
	}
}

void ABossActor::TickMove()
{
	FVector loc = UKismetMathLibrary::VLerp(origin, moveTarget->GetActorLocation(), alpha);

	SetActorLocation(loc);

	alpha += GetWorld()->GetDeltaSeconds() / speedRate;

	if (alpha >= 1)
	{
		state = EBossState::Attack
	}
}

void ABossActor::TickAttack()
{
	
}

