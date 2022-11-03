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
	//boxComp->SetCollisionResponseToAllChannels(ECR_Ignore);  //�������Ʈ Detailsâ Collision���� ���� Ignore�� ������ �Ͱ� ���� ���.
	//boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);  //�ش� ä�ΰ��� ���� Overlap �ϰڴٴ� ����.

	//�浹ó�� case2: Preset�� �̿�.
	boxComp->SetGenerateOverlapEvents(true);
	boxComp->SetCollisionProfileName(TEXT("Bullet"));

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ABulletActor::OnBoxComponentBeginOverlap);

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

	//���� �̵��ϰ�ʹ�.
	//p = p0 + vt
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * speed * DeltaTime);

}

void ABulletActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//Bullet�� �ε��� ��밡 Enemy��� Bullet�� Enemy �� �� �Ҹ�.
	//if (OtherActor->IsA(AEnemyActor::StaticClass()))
	//{
	//	OtherActor->Destroy();
	//	
	//	this->Destroy();  //���� Component��� this�� �ƴ϶� Owner�� �־�� �Ѵ�.
	//}
	//IsA�� ó�� ���ϰ�, if else else ... else if ���·� ����ȴ�. if else�� ��� �ߺ��Ͽ� ����ϴ� ����� �ƴϴ�. ������ ȿ���鿡�� ����.


	//if (OtherActor->GetName().Contains(TEXT("Enemy")));  //Contains()�� ���ڿ����� ���δ� ���� ������ �̷���� ȿ���鿡�� �����ʴ�.
	//����, ���� ã������ �ϴ� ���̹Ƿ�, Enemy1, Enemy2��� ���������� EnemyBullet���� ���� �ִٸ� �̰͵� Enemy��� ���ڿ��� ���ԵǾ� �ֱ� ������ �̰͵� �ҷ��� ������.



	/*
	AEnemyActor* enemy = Cast<AEnemyActor>(OtherActor);
	if (enemy != nullptr)
	{
		Destroy.
	}
	else {
		AEnemyActor* player = Cast<AEnemyActor>(OtherActor);
		if(player != nullptr) { } else { } ... if() { } else { } ...
	}
	Cast ����� �� ���ŷӴ�.
	Cast�� ���ؼ� ��� Ȯ���ϴ� �������, if else���� ��� ���ȴ�.
	ó���� ���Ͽ� Ȯ���ϰ� �ƴϸ� �ٸ����� ���ϰ�, �̰͵� �ƴϸ� if else���� �� ����Ѵ�.
	Cast�ȿ� IsA�� ���ԵǾ� �����Ƿ�, IsA�� ����ϸ� �ȴ�.
	*/
}

void ABulletActor::OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AEnemyActor::StaticClass()))
	{
		auto enemy = Cast<AEnemyActor>(OtherActor);  //OtherActor�� AEnemyAcotr�� ��ȯ. auto�� �ڷ����� �ڵ��� �������ش�. ���⼭ auto�� AEnemyActor* �̴�.
		enemy->Explosion();
		
		//��� �ı�
		OtherActor->Destroy();

		//�ڽ� �ı�.
		this->Destroy();
	}
}

