// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestroyZoneActor.generated.h"

UCLASS()
class MYFIRSTSHOOTINGCPP_API ADestroyZoneActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestroyZoneActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//충돌체
	UPROPERTY(EditAnywhere)
		class UBoxComponent* boxComp;


	//충돌처리 함수
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
