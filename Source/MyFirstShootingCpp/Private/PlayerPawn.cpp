// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include <Components/ArrowComponent.h>
#include "BulletActor.h"
#include <Kismet/GameplayStatics.h>  //UGameplayStatics::PlaySound2D(GetWorld(), fireSound); �� ����ϱ� ���� ��� ����.
#include <Components/BoxComponent.h>
#include "EnemyActor.h"

//void APlayerPawn::OnActionFire()���� �����ϴ� bulletFactory, firePosition �� ���� ���� ����ϱ� ���� ����� �߰��� �ִ� ���̴�.

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	//boxComp�� Root�� �ϰ� �ʹ�.
	RootComponent = boxComp;

	//�浹ó�� case2: Preset�� �̿�.
	boxComp->SetGenerateOverlapEvents(true);
	boxComp->SetCollisionProfileName(TEXT("Player"));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(RootComponent);



	firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("firePosition"));
	firePosition->SetRelativeLocation(FVector(0, 0, 100));  //Relative, �θ�κ��� ������ ���� ��. FVector�� �ڷ����̴�.
	firePosition->SetRelativeRotation(FRotator(90, 0, 0));  //ȸ����: y, z, x ������ �Է�.
	firePosition->SetupAttachment(RootComponent);  //ó������ meshComp�� �پ��־�����, mesh�� ������ �������� arrow�� ���ư��� arrow�� root�� �ٿ��� ���̴�.

	meshComp->SetRelativeRotation(FRotator(0, 90, 90));  //FRotator(pitch, yaw, roll);
	meshComp->SetRelativeScale3D(FVector(3.0f));  //Scale�� �����ϴ� �Լ��� SetRelativeScale3D�̰�, �ش� ���ڿ� �ϳ��� ���� ���� �ѹ��� ���� �ٲٴ� ��. 3���� ���ڸ� �־��ָ� x, y, z�� ���� �ٲ��ִ� ���̴�.


}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//������� �Է�(��)���� ������ �����
	
	FVector direction = FVector(0, h, v);  //FVertor()��� GetActorRightVector() * h + GetActorUpVector() * v; ���.
	//FVector()�� ������ǥ�̴�. 2D���ӿ����� ũ�� ����̾�����, actor�� ������ ���ư���, �� �������� ���� ���ϱ� ������, �ش� �������� �� �� �ְ� ����� ���� GetActor Vector�� ����Ͽ� �� ���̴�.
	direction.Normalize();
	//�� �������� �̵��ϰ� �ʹ�. p = p0 + vt
	FVector p0 = GetActorLocation();
	FVector velocity = direction * speed;
	//GetWorld()->GetDeltaSeconds();  //DeltaTime�� ����)
	float t = DeltaTime;
	
	SetActorLocation(p0 + velocity * t);
	//�� �ٷ� ǥ��: SetActorLocation(GetActorLocation() + FVector(0, h, v) * speed * DeltaTime);


}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &APlayerPawn::OnAxisHorizontal);

	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &APlayerPawn::OnAxisVertical);

	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &APlayerPawn::OnActionFire);

}

void APlayerPawn::OnAxisHorizontal(float value)  //Axis�� �Լ� ȣ��ȴ�.
{
	h = value;
}

void APlayerPawn::OnAxisVertical(float value)
{
	v = value;
}

void APlayerPawn::OnActionFire()
{
	GetWorld()->SpawnActor<ABulletActor>(bulletFactory, firePosition->GetComponentTransform());
	/*GetWorld*/

	
	UGameplayStatics::PlaySound2D(GetWorld(), fireSound);
}

void APlayerPawn::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->IsA(AEnemyActor::StaticClass()))
	{
		OtherActor->Destroy();

		this->Destroy();  //���� Component��� this�� �ƴ϶� Owner�� �־�� �Ѵ�.
	}
}