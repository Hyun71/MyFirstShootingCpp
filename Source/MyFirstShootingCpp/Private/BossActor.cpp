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

	//if���� ����Ͽ� ���ϴ� ���°��� �����Ŵ.
	/*if (state == EBossState::Move)
	{

	}
	else if(state == EBossState::Attack)*/
	
	switch (state)
	{
	case EBossState::Move:
		TickMove();  //���⿡ �����ϸ� �ʹ� �����ϹǷ� ���� �Լ��� ���� �����Ѵ�.
		break;
	case EBossState::Attack:
		TickAttack();
		break;
	}
}

void ABossActor::TickMove()
{
	FVector loc = UKismetMathLibrary::VLerp(origin, moveTarget->GetActorLocation(), alpha);  //��� ���� �ʿ�. #include <Kismet/KismetMathLibrary.h>

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
		//�ð��� �帣�ٰ�
		currentTime += GetWorld()->GetDeltaSeconds();
		//�߻�ð��� �Ǹ�
		if (currentTime > fireTime)
		{
			currentTime = 0;
			//�� �Ѿ� ���忡�� �Ѿ��� 12�� ���� 360���� ��� �ʹ�.
			FQuat zeroQ = FQuat(FRotator(90, 0, 0)); //FQuat�� ���ʹϾ� �ڷ���
			for (int i = 0; i < 12; i++)
			{
				FQuat addQ = FQuat(FRotator(0, i * 30, 0));
				FRotator angle = FRotator(zeroQ * addQ);  //���ʹϾ��� ���� �����̴�. ���� ���� �������ͷ� ��ȯ. ���� ������ ���� ������ �����ָ�, ���ο� ���� ������ ��� �ҷ��´�.
				MakeEnemyBullet(GetActorLocation(), angle);
			}

		}
	}
	else  //���� ������ �Ѿ� �߻� ����
	{
		currentTime += GetWorld()->GetDeltaSeconds();
		if (currentTime > shotFireTime)
		{
			currentTime = 0;
			float shotAngle = 360 / shotMaxIndex;  //�ѹ� �ѹ� �Ѿ� ���� ����.
		
			FQuat zeroQ = FQuat(FRotator(90, 0, 0)); //FQuat�� ���ʹϾ� �ڷ���
			FQuat addQ = FQuat(FRotator(0, shotIndex * shotAngle, 0));  //shotIndex�� 0���� ����.
			FRotator angle = FRotator(zeroQ * addQ);  //���ʹϾ��� ���� �����̴�. ���� ���� �������ͷ� ��ȯ. ���� ������ ���� ������ �����ָ�, ���ο� ���� ������ ��� �ҷ��´�.
			MakeEnemyBullet(GetActorLocation(), angle);

			shotIndex++;
			if (++shotIndex > shotMaxIndex)
			{
				shotIndex = 0;
			}  //shotIndex = (shotIndex + 1) % shotMaxIndex; ó�� �� �ٷ� �ۼ��� ���� �ִ�. ������.
			//shotIndex = (shotIndex + shotMaxIndex - 1) % shotMaxIndex;  ������.
		}
	}
}

void ABossActor::MakeEnemyBullet(FVector loc, FRotator angle)
{
	GetWorld()->SpawnActor<AEnemyBulletActor>(enemyBulletFactory, loc, angle);  //��� ���� �ʿ�. #include "EnemyBulletActor.h"


}

