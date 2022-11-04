// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"
#include <Components/BoxComponent.h>
#include <Kismet/GameplayStatics.h>
#include "BulletActor.h"
#include "PlayerPawn.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
AEnemyActor::AEnemyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	//boxComp�� Root�� �ϰ� �ʹ�.
	RootComponent = boxComp;

	//�浹ó�� case2: Preset�� �̿�.
	boxComp->SetGenerateOverlapEvents(true);
	boxComp->SetCollisionProfileName(TEXT("Enemy"));

	boxComp->SetBoxExtent(FVector(50, 50, 50));
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::OnBoxComponentBeginOverlap);  //�ּҰ��� �ִ� ������  TEXT("OnBoxComponentBeginOverlap") ���� �ۼ��ص� �ȴ�.
	//���ξ�On�� �ڵ����� �޴� �Լ�. �� �Լ��� �浹�� �Ͼ�� �� �Ҹ��� �Լ�.
	//Dynamic�� ����, UFUNCTION�� ������־�� �Ѵ�.


	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(RootComponent);  //���� ������ �̱� ������, RootComponent�� boxComp�� �ּҰ��� �� �ִ�.



}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();

	//�¾ �� ������ ���ϰ� �ʹ�. 30% Ȯ���� �÷��̾� ����, �������� �� �������� �����ϰ� �ʹ�.
	float result = FMath::FRandRange(0.0f, 1.0f);  //FMath: ���п� ���� ��ƿ��Ƽ Ŭ����
	if (result < 0.3f)
	{
		//�÷��̾� ����
		auto target = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		direction = target->GetActorLocation() - GetActorLocation();
		direction.Normalize();
	}
	else {
		//�� ����
		direction = GetActorForwardVector();
	}

	//�̵��������� ȸ���ϰ� �ʹ�.
	auto rot = UKismetMathLibrary::MakeRotFromXZ(direction, GetActorUpVector());
	SetActorRotation(rot);
	
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//�� �������� �̵��ϰ� �ʹ�.
	//p = p0 + vt
	SetActorLocation(GetActorLocation() + direction * speed * DeltaTime);
}

void AEnemyActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	//if (OtherActor->IsA(APlayerPawn::StaticClass()))  // OR�� ����ص� �ȴ�.
	//{
	//	OtherActor->Destroy();

	//	this->Destroy();  //���� Component��� this�� �ƴ϶� Owner�� �־�� �Ѵ�.
	//}
	//else if (OtherActor->IsA(ABulletActor::StaticClass()) {
	//	OtherActor->Destroy();

	//	this->Destroy();  //���� Component��� this�� �ƴ϶� Owner�� �־�� �Ѵ�.
	//}
	
}

void AEnemyActor::OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(APlayerPawn::StaticClass()))  // OR�� ����ص� �ȴ�.
	{
		OtherActor->Destroy();

		this->Destroy();  //���� Component��� this�� �ƴ϶� Owner�� �־�� �Ѵ�.
		Explosion();
	}
	else if (OtherActor->IsA(ABulletActor::StaticClass())) {
		OtherActor->Destroy();

		this->Destroy();  //���� Component��� this�� �ƴ϶� Owner�� �־�� �Ѵ�.
		Explosion();
	}
}

void AEnemyActor::Explosion()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionVFXFactory, GetActorLocation());
}
//���⼭ Enemy�� �浹�ϴ� Player�� Bullet �浹ü�� �����Ͽ����Ƿ�, �� ���� �ش� cpp���� ���� ������ �ʿ�� ����. �� �����ϸ� ���� �ν÷��� �ϸ鼭 ������ �� �� �ִ�.