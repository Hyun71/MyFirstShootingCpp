// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include "BulletActor.h"
#include "PlayerPawn.h"

// Sets default values
AEnemyActor::AEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	//boxComp를 Root로 하고 싶다.
	RootComponent = boxComp;

	//충돌처리 case2: Preset을 이용.
	boxComp->SetGenerateOverlapEvents(true);
	boxComp->SetCollisionProfileName(TEXT("Enemy"));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(RootComponent);  //전부 포인터 이기 때문에, RootComponent에 boxComp의 주소값이 들어가 있다.


}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();

	//태어날 때 방향을 정하고 싶다. 30% 확률로 플레이어 방향, 나머지는 앞 방향으로 결정하고 싶다.
	float result = FMath::FRandRange(0.0f, 1.0f);
	if (result < 0.3f)
	{
		//플레이어 방향
		auto target = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		direction = target->GetActorLocation() - GetActorLocation();
		direction.Normalize();
	}
	else {
		//앞 방향
		direction = GetActorForwardVector();
	}
	
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//그 방향으로 이동하고 싶다.
	//p = p0 + vt
	SetActorLocation(GetActorLocation() + direction * speed * DeltaTime);
}

void AEnemyActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->IsA(APlayerPawn::StaticClass()))  // OR를 사용해도 된다.
	{
		OtherActor->Destroy();

		this->Destroy();  //만약 Component라면 this가 아니라 Owner를 넣어야 한다.
	}
	else if (OtherActor->IsA(ABulletActor::StaticClass())) {
		OtherActor->Destroy();

		this->Destroy();  //만약 Component라면 this가 아니라 Owner를 넣어야 한다.
	}
	//여기서 Enemy와 충돌하는 Player와 Bullet 충돌체를 구현하였으므로, 이 둘은 해당 cpp에서 따로 구현할 필요는 없다. 또 구현하면 서로 부시려고 하면서 오류가 날 수 있다.
}