// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossActor.generated.h"


UENUM(BlueprintType)
enum class EBossState : uint8 {  //¿­°ÅÇü
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

	EBossState state = EBossState::Idle;

	FVector origin;

	float alpha = 0;
	float speedRate = 1;

	UPROPERTY(EditAnywhere)
		AActor* moveTarget;

	void TickMove();
	void TickAttack();
};
