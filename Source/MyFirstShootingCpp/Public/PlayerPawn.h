// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class MYFIRSTSHOOTINGCPP_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float h;
	float v;
	void OnAxisHorizontal(float value);
	void OnAxisVertical(float value);

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* meshComp;
	float speed = 500.0f;  //500이라고만 쓰면, 내부적으로 형변환이 일어나버린다.

	//화살표시(FirePosition)
	UPROPERTY(EditAnywhere)
	class UArrowComponent* firePosition;
	
	//BP_Bullet을 담을 포인터변수
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABulletActor> bulletFactory;
	//TSubclassof는 spawn하고자 하는 것을 선언할 때 사용한다.
	//bulletFactory라는 변수를 생성한 것.
	/*총알 1, 2, 3 이 있고, 최상위 parent로 ABulletActor가 있다면, 
	이 parent로 스폰할 클래스 변수를 만든다.
	만들어진 변수는 아직 채워지지 않은 변수로, UPROPERTY()를 통해 
	블루프린트에서 볼 수 있게 만들고, 거기서 원하는 총알을 선택하여 
	채워넣으면 되는 것이다.
	*/


	void OnActionFire();  //Action에 대한 바인딩.
};
