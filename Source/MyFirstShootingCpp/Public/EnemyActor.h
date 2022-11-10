// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyActor.generated.h"

UCLASS()
class MYFIRSTSHOOTINGCPP_API AEnemyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;  //충돌을 구현하기 위한 선언.
	//해당 충돌은 '충돌, 그리고 충돌한 개체만' 감지한다. 어느 부분에 부딪혔는지에 관한 것은 감지하지 못한다.


	UFUNCTION()
		void OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//이 충돌은, 예로들면 충돌이 손, 손목, 팔 등 처럼 어디에 부딪혔는지도 감지할 수 있는 충돌이다.

	//몸을 만들고 싶다.
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* meshComp;  //Enemy mesh 생성.

	UPROPERTY(EditAnywhere)
		class UBoxComponent* boxComp;  //충돌체 정의. Box, Sphere, Capsule 3가지 충돌체가 있다.

	//태어날 때 방향을 정하고 싶다. 30% 확률로 플레이어 방향, 나머지는 앞 방향으로 결정하고 싶다.
	
	//살아가면서 그 방향으로 이동하고 싶다.
	FVector direction;

	float speed = 500;

public:
	//Enemy가 누군가(Bullet, Player)와 부딪히면 폭발하고 싶다.
	//시각효과: VFX
	UPROPERTY(EditAnywhere)
		class UParticleSystem* explosionVFXFactory;

	void Explosion();


	FTimerHandle timerHandleMakeBullet;  //타이머를 멈추고 싶을 때 사용. 총알 멈추게 하고 싶을 때 사용.
	UPROPERTY(EditAnywhere)
		float makeMin = 0.5f;
	UPROPERTY(EditAnywhere)
		float makeMax = 1.0f;


	UPROPERTY(EditAnywhere)
		TSubclassOf<class AEnemyBulletActor> enemyBulletFactory;

	void MakeEnemyBullet();  //이 함수를 타이머에 등록하여 사용할 것이다.
};