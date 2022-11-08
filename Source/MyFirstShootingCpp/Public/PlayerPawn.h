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

	//virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float h;
	float v;
	void OnAxisHorizontal(float value);
	void OnAxisVertical(float value);

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* meshComp;
	float speed = 500.0f;  //500�̶�� ����, ���������� ����ȯ�� �Ͼ������.

	//ȭ��ǥ��(FirePosition)
	UPROPERTY(EditAnywhere)
	class UArrowComponent* firePosition;
	
	//BP_Bullet�� ���� �����ͺ���
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABulletActor> bulletFactory;
	//TSubclassof�� spawn�ϰ��� �ϴ� ���� ������ �� ����Ѵ�.
	//bulletFactory��� ������ ������ ��.
	/*�Ѿ� 1, 2, 3 �� �ְ�, �ֻ��� parent�� ABulletActor�� �ִٸ�, 
	�� parent�� ������ Ŭ���� ������ �����.
	������� ������ ���� ä������ ���� ������, UPROPERTY()�� ���� 
	�������Ʈ���� �� �� �ְ� �����, �ű⼭ ���ϴ� �Ѿ��� �����Ͽ� 
	ä�������� �Ǵ� ���̴�.
	*/


	void OnActionFire();  //Action�� ���� ���ε�.


	//void SetupInput(class UInputComponent* PlayerInputComponent);
	//Component�� ����� �ش� SetupInput�� �ڵ������Ǿ� ���� �ʾƼ�, �������־�� �Ѵ�.

	UPROPERTY(EditAnywhere)
		class USoundBase* fireSound;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* boxComp;


	int hp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int maxHP = 5;

	//Event �Լ�, Callback�Լ�.
	void OnMyHit(int damage);  //�������� ȣ���� �ִ� �Լ��� ǥ���ϱ� ���� On�� �ٿ���.

	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable) Native�� Implement�� ����???

	//Ŀ���� �̺�Ʈ
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)  //Implement�� C++������ ������ ���� �ʾƼ� �������Ʈ���� �����ؾ� �Ѵ�.
	void OnMyUpdateHealth(int value);


	//Callable�� ���� ���� �ִ�. Pure�� ���� ���� ����.
};
