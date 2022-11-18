// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossActor.generated.h"


UENUM(BlueprintType)
enum class EBossState : uint8 {  //열거형. 상태머신 제어하기 위한 열거형.
	Idle,
	Move,
	Attack,
};

UCLASS()
class MYFIRSTSHOOTINGCPP_API ABossActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBossState state = EBossState::Idle;

	FVector origin;

	float alpha = 0;
	float speedRate = 1;

	UPROPERTY(EditAnywhere)
		AActor* moveTarget;

	void TickMove();
	void TickAttack();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemyBulletActor> enemyBulletFactory;

	float currentTime;
	float fireTime = 2;  //총알 몇 초에 한 번씩 발사할지에 관한 변수.

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bfireOneShot;  //true: 한 번에 쏘는 것, false : 나선형

	void MakeEnemyBullet(FVector origin, FRotator angle);  //총알 만들 때 필요한 정보가 있다. Rotator필요. 생성위치와 방향 정보.


	//나선형태의 총알 발사
	int shotIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int shotMaxIndex = 12;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float shotFireTime = 0.05f;  //얼마나 다음 총알을 빨리 쏘는지.
};
