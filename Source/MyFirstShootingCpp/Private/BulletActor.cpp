// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"
#include <Components/StaticMeshcomponent.h>  //UStaticMeshComponent���� �ڷ����� ����ϱ� ����. ������ BulletActor.h ������ϳ��� ������, ���� ���� �� ��� �� ������� �ʿ�.
#include <Components/BoxComponent.h>
#include "EnemyActor.h"

// Sets default values
ABulletActor::ABulletActor()  //BulletActor�� ������.
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	//boxComp�� Root�� �ϰ� �ʹ�.
	RootComponent = boxComp;
	

	//�浹ó�� case1.
	////Collision Settings. Blueprint�� �ִ� Detailsâ Collision �κ��� �����Ͽ� �ۼ��ϸ� ���ϴ�.
	//boxComp->SetGenerateOverlapEvents(true);
	//boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//boxComp->SetCollisionObjectType(ECC_GameTraceChannel3);  //Project Settings - Engine - Collision���� ���� ������� ä�� ������ �����ؼ� ����ص� �ȴ�. 1���� ����. �ƴϸ�, �� ������Ʈ ������ ���� Config������ �ִ� DefaultEngine.ini�� �ִ� DefaultChannelResponse�κп��� �ش� ä���� �������� �ȴ�.
	//boxComp->SetCollisionResponseToAllChannels(ECR_Ignore);  //��������Ʈ Detailsâ Collision���� ���� Ignore�� ������ �Ͱ� ���� ���.
	//boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);  //�ش� ä�ΰ��� ���� Overlap �ϰڴٴ� ����.

	//�浹ó�� case2: Preset�� �̿�.
	boxComp->SetGenerateOverlapEvents(true);
	boxComp->SetCollisionProfileName(TEXT("Bullet"));



	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//���� �̵��ϰ��ʹ�.
	//p = p0 + vt
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * speed * DeltaTime);

}

void ABulletActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//Bullet�� �ε��� ��밡 Enemy��� Bullet�� Enemy �� �� �Ҹ�.
	if (OtherActor->IsA(AEnemyActor::StaticClass()))
	{
		OtherActor->Destroy();
		
		this->Destroy();  //���� Component��� this�� �ƴ϶� Owner�� �־�� �Ѵ�.
	}


	//if (OtherActor->GetName().Contains(TEXT("Enemy"))); Contains()�� ���� �� �о ã��.

	/*AEnemyActor* enemy = Cast<AEnemyActor>(OtherActor);
	if (enemy != nullptr)
	{

	}
	else {
		AEnemyActor* player = Cast<AEnemyActor>(OtherActor);
		if(player != nullptr)
	}*/
}
