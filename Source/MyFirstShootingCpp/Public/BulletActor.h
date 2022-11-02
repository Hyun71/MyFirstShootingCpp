// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletActor.generated.h"

UCLASS()
class MYFIRSTSHOOTINGCPP_API ABulletActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;  //virtual을 해줌으로써 재정의 하여 사용하는 것. 부모의 것을 동일하게 사용하는것이 아니다.

	//UStaticMeshComponent 의 meshComp
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* meshComp;
	//위로 이동하고싶다.
	UPROPERTY(EditAnywhere)
		float speed = 1000;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* boxComp;
};
