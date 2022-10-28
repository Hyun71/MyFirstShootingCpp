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

	//�¾�� ���� target�� nullptr�̶�� BP_PlayerPawn�� ã�Ƽ� �������� ��� �ʹ�.
	if (target == nullptr) { // ! �� ���� ��Ų�ٴ� �ǹ�.
		target = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	}
}

// Called every frame
void ATailActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//��ư��鼭 �������� ���ϴ� ������ ���ϰ� �̵��ϰ� �ʹ�.
	FVector dir = target->GetActorLocation() - GetActorLocation();  //this���� ����.
	dir.Normalize();
	SetActorLocation(GetActorLocation() + dir * speed * DeltaTime);
}

