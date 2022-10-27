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

}

void APlayerPawn::OnAxisHorizontal(float value)  //Axis�� �Լ� ȣ��ȴ�.
{
	h = value;
}

void APlayerPawn::OnAxisVertical(float value)
{
	v = value;
}

