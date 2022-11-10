// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBulletActor.h"
#include <Components/BoxComponent.h>
#include "BulletActor.h"
#include "PlayerPawn.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AEnemyBulletActor::AEnemyBulletActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	//boxComp를 Root로 하고 싶다.
	RootComponent = boxComp;

	//충돌처리 case2: Preset을 이용.
	boxComp->SetGenerateOverlapEvents(true);
	boxComp->SetCollisionProfileName(TEXT("EnemyBullet"));

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBulletActor::OnBoxComponentBeginOverlap);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEnemyBulletActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyBulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//이동.
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * speed * DeltaTime);


}

void AEnemyBulletActor::OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//APlayerPawn, ABulletActor 충돌.
	if (OtherActor->IsA(ABulletActor::StaticClass()))  //적 객체의 총알과 플레이어의 총알 충돌.  alt + shift + Q => 헤더 자동으로 추가해준다(tomato 사용시에만).
	{
		Explosion();

		//상대 파괴
		OtherActor->Destroy();

		//자신 파괴.
		this->Destroy();


	}
	else if (OtherActor->IsA(APlayerPawn::StaticClass()))  //적 객체의 총알과 플레이어의 충돌.
	{
		Explosion();

		//너 Hit하고
		auto player = Cast<APlayerPawn>(OtherActor);
		player->OnMyHit(1);

		//나죽고 하고싶다.
		this->Destroy();
	}
}

void AEnemyBulletActor::Explosion()  //alt + enter(visual studio제공), alt + shift + Q(tomato제공) -> 선언부 구현.
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionVFXFactory, GetActorLocation());
}