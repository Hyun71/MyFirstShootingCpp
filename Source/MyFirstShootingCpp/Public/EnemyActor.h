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

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;  //�浹�� �����ϱ� ���� ����.
	//�ش� �浹�� '�浹, �׸��� �浹�� ��ü��' �����Ѵ�. ��� �κп� �ε��������� ���� ���� �������� ���Ѵ�.


	UFUNCTION()
		void OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//�� �浹��, ���ε�� �浹�� ��, �ո�, �� �� ó�� ��� �ε��������� ������ �� �ִ� �浹�̴�.

	//���� ����� �ʹ�.
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* meshComp;  //Enemy mesh ����.

	UPROPERTY(EditAnywhere)
		class UBoxComponent* boxComp;  //�浹ü ����. Box, Sphere, Capsule 3���� �浹ü�� �ִ�.

	//�¾ �� ������ ���ϰ� �ʹ�. 30% Ȯ���� �÷��̾� ����, �������� �� �������� �����ϰ� �ʹ�.
	
	//��ư��鼭 �� �������� �̵��ϰ� �ʹ�.
	FVector direction;

	float speed = 500;

public:
	//Enemy�� ������(Bullet, Player)�� �ε����� �����ϰ� �ʹ�.
	//�ð�ȿ��: VFX
	UPROPERTY(EditAnywhere)
		class UParticleSystem* explosionVFXFactory;

	void Explosion();
};