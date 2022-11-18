// Fill out your copyright notice in the Description page of Project Settings.


#include "BossActor.h"
#include <Kismet/KismetMathLibrary.h>
#include "EnemyBulletActor.h"


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
	FVector loc = UKismetMathLibrary::VLerp(origin, moveTarget->GetActorLocation(), alpha);  //헤더 파일 필요. #include <Kismet/KismetMathLibrary.h>

	SetActorLocation(loc);

	alpha += GetWorld()->GetDeltaSeconds() / speedRate;

	if (alpha >= 1)
	{
		state = EBossState::Attack;
	}
}

void ABossActor::TickAttack()
{
	if (bfireOneShot)
	{
		//시간이 흐르다가
		currentTime += GetWorld()->GetDeltaSeconds();
		//발사시간이 되면
		if (currentTime > fireTime)
		{
			currentTime = 0;
			//적 총알 공장에서 총알을 12발 만들어서 360도로 쏘고 싶다.
			FQuat zeroQ = FQuat(FRotator(90, 0, 0)); //FQuat는 쿼터니언 자료형
			for (int i = 0; i < 12; i++)
			{
				FQuat addQ = FQuat(FRotator(0, i * 30, 0));
				FRotator angle = FRotator(zeroQ * addQ);  //쿼터니언의 곱은 덧셈이다. 곱한 다음 로테이터로 변환. 기준 각도와 더할 각도를 더해주며, 새로운 기준 각도를 계속 불러온다.
				MakeEnemyBullet(GetActorLocation(), angle);
			}

		}
	}
	else  //나선 형태의 총알 발사 구현
	{
		currentTime += GetWorld()->GetDeltaSeconds();
		if (currentTime > shotFireTime)
		{
			currentTime = 0;
			float shotAngle = 360 / shotMaxIndex;  //한발 한발 총알 각도 구함.
		
			FQuat zeroQ = FQuat(FRotator(90, 0, 0)); //FQuat는 쿼터니언 자료형
			FQuat addQ = FQuat(FRotator(0, shotIndex * shotAngle, 0));  //shotIndex는 0부터 시작.
			FRotator angle = FRotator(zeroQ * addQ);  //쿼터니언의 곱은 덧셈이다. 곱한 다음 로테이터로 변환. 기준 각도와 더할 각도를 더해주며, 새로운 기준 각도를 계속 불러온다.
			MakeEnemyBullet(GetActorLocation(), angle);

			shotIndex++;
			if (++shotIndex > shotMaxIndex)
			{
				shotIndex = 0;
			}  //shotIndex = (shotIndex + 1) % shotMaxIndex; 처럼 한 줄로 작성할 수도 있다. 순방향.
			//shotIndex = (shotIndex + shotMaxIndex - 1) % shotMaxIndex;  역방향.
		}
	}
}

void ABossActor::MakeEnemyBullet(FVector loc, FRotator angle)
{
	GetWorld()->SpawnActor<AEnemyBulletActor>(enemyBulletFactory, loc, angle);  //헤더 파일 필요. #include "EnemyBulletActor.h"


}

