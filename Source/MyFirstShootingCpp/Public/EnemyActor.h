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


	UFUNCTION()
		void OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//On

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
};
