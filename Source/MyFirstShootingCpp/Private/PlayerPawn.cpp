// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));

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

}

void APlayerPawn::OnAxisHorizontal(float value)  //Axis가 게속 호출된다.
{
	h = value;
}

void APlayerPawn::OnAxisVertical(float value)
{
	v = value;
}

