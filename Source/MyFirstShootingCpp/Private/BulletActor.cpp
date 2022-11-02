// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletActor.h"
#include <Components/StaticMeshcomponent.h>  //UStaticMeshComponent같은 자료형을 사용하기 위함. 원래는 BulletActor.h 헤더파일내에 있지만, 만약 따로 쓸 경우 이 헤더파일 필요.
#include <Components/BoxComponent.h>
#include "EnemyActor.h"

// Sets default values
ABulletActor::ABulletActor()  //BulletActor의 생성자.
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	//boxComp를 Root로 하고 싶다.
	RootComponent = boxComp;
	

	//충돌처리 case1.
	////Collision Settings. Blueprint에 있는 Details창 Collision 부분을 참고하여 작성하면 편하다.
	//boxComp->SetGenerateOverlapEvents(true);
	//boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//boxComp->SetCollisionObjectType(ECC_GameTraceChannel3);  //Project Settings - Engine - Collision에서 만든 순서대로 채널 순서로 유추해서 사용해도 된다. 1부터 시작. 아니면, 이 프로젝트 폴더로 들어가서 Config폴더에 있는 DefaultEngine.ini에 있는 DefaultChannelResponse부분에서 해당 채널을 가져오면 된다.
	//boxComp->SetCollisionResponseToAllChannels(ECR_Ignore);  //블루프린트 Details창 Collision에서 전부 Ignore를 선택한 것과 같은 결과.
	//boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);  //해당 채널과는 전부 Overlap 하겠다는 설정.

	//충돌처리 case2: Preset을 이용.
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

	//위로 이동하고싶다.
	//p = p0 + vt
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * speed * DeltaTime);

}

void ABulletActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//Bullet에 부딪힌 상대가 Enemy라면 Bullet과 Enemy 둘 다 소멸.
	if (OtherActor->IsA(AEnemyActor::StaticClass()))
	{
		OtherActor->Destroy();
		
		this->Destroy();  //만약 Component라면 this가 아니라 Owner를 넣어야 한다.
	}


	//if (OtherActor->GetName().Contains(TEXT("Enemy"))); Contains()는 전부 다 읽어서 찾음.

	/*AEnemyActor* enemy = Cast<AEnemyActor>(OtherActor);
	if (enemy != nullptr)
	{

	}
	else {
		AEnemyActor* player = Cast<AEnemyActor>(OtherActor);
		if(player != nullptr)
	}*/
}

