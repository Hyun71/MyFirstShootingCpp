// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include <Components/ArrowComponent.h>
#include "BulletActor.h"
#include <Kismet/GameplayStatics.h>  //UGameplayStatics::PlaySound2D(GetWorld(), fireSound); 를 사용하기 위한 헤더 파일.
#include <Components/BoxComponent.h>
#include "EnemyActor.h"

//void APlayerPawn::OnActionFire()에서 구현하는 bulletFactory, firePosition 를 오류 없이 사용하기 위해 헤더를 추가해 주는 것이다.

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	//boxComp를 Root로 하고 싶다.
	RootComponent = boxComp;

	//충돌처리 case2: Preset을 이용.
	boxComp->SetGenerateOverlapEvents(true);
	boxComp->SetCollisionProfileName(TEXT("Player"));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(RootComponent);



	firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("firePosition"));
	firePosition->SetRelativeLocation(FVector(0, 0, 100));  //Relative, 부모로부터 떨어진 나의 값. FVector는 자료형이다.
	firePosition->SetRelativeRotation(FRotator(90, 0, 0));  //회전값: y, z, x 순서로 입력.
	firePosition->SetupAttachment(RootComponent);  //처음에는 meshComp에 붙어있었지만, mesh를 돌리는 과정에서 arrow도 돌아가서 arrow는 root에 붙여준 것이다.

	meshComp->SetRelativeRotation(FRotator(0, 90, 90));  //FRotator(pitch, yaw, roll);
	meshComp->SetRelativeScale3D(FVector(3.0f));  //Scale을 설정하는 함수는 SetRelativeScale3D이고, 해당 인자에 하나의 값이 들어가면 한번에 값을 바꾸는 것. 3개의 인자를 넣어주면 x, y, z값 각각 바꿔주는 것이다.


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

	//사용자의 입력(축)으로 방향을 만들고
	
	FVector direction = FVector(0, h, v);  //FVertor()대신 GetActorRightVector() * h + GetActorUpVector() * v; 사용.
	//FVector()는 절대좌표이다. 2D게임에서는 크게 상관이없지만, actor가 방향이 돌아가면, 그 방향으로 가지 못하기 때문에, 해당 방향으로 갈 수 있게 만들기 위해 GetActor Vector를 사용하여 준 것이다.
	direction.Normalize();
	//그 방향으로 이동하고 싶다. p = p0 + vt
	FVector p0 = GetActorLocation();
	FVector velocity = direction * speed;
	//GetWorld()->GetDeltaSeconds();  //DeltaTime과 같다)
	float t = DeltaTime;
	
	SetActorLocation(p0 + velocity * t);
	//한 줄로 표현: SetActorLocation(GetActorLocation() + FVector(0, h, v) * speed * DeltaTime);


}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &APlayerPawn::OnAxisHorizontal);

	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &APlayerPawn::OnAxisVertical);

	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &APlayerPawn::OnActionFire);

}

void APlayerPawn::OnAxisHorizontal(float value)  //Axis가 게속 호출된다.
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

		this->Destroy();  //만약 Component라면 this가 아니라 Owner를 넣어야 한다.
	}
}