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
	//boxComp�� Root�� �ϰ� �ʹ�.
	RootComponent = boxComp;

	//�浹ó�� case2: Preset�� �̿�.
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

	//�̵�.
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * speed * DeltaTime);


}

void AEnemyBulletActor::OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//APlayerPawn, ABulletActor �浹.
	if (OtherActor->IsA(ABulletActor::StaticClass()))  //�� ��ü�� �Ѿ˰� �÷��̾��� �Ѿ� �浹.  alt + shift + Q => ��� �ڵ����� �߰����ش�(tomato ���ÿ���).
	{
		Explosion();

		//��� �ı�
		OtherActor->Destroy();

		//�ڽ� �ı�.
		this->Destroy();


	}
	else if (OtherActor->IsA(APlayerPawn::StaticClass()))  //�� ��ü�� �Ѿ˰� �÷��̾��� �浹.
	{
		Explosion();

		//�� Hit�ϰ�
		auto player = Cast<APlayerPawn>(OtherActor);
		player->OnMyHit(1);

		//���װ� �ϰ�ʹ�.
		this->Destroy();
	}
}

void AEnemyBulletActor::Explosion()  //alt + enter(visual studio����), alt + shift + Q(tomato����) -> ����� ����.
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionVFXFactory, GetActorLocation());
}