// Fill out your copyright notice in the Description page of Project Settings.


#include "EntityBase.h"
#include "Client.h"
#include "Engine/KBEngine.h"
#include "MainGameModeBase.h"
#include "Engine/Entity.h"

 //Sets default values
AEntityBase::AEntityBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	entityID = 0;
	moveSpeed = 0.f;
	isOnGround = false;
	isPlayerCharacter = false;
}

// Called when the game starts or when spawned
void AEntityBase::BeginPlay()
{
	Super::BeginPlay();

	auto XGameMode = Cast<AMainGameModeBase>(UGameplayStatics::GetGameMode(this));

	if (XGameMode)
	{
		// ���Լ�ע�ᵽAMainGameModeBase������������
		XGameMode->addGameEntity(this->entityID, this);
		KBEngine::Entity* pEntity = KBEngine::KBEngineApp::getSingleton().findEntity(entityID);

		// ����UE4���ӻ�ʵ�崴��Ҫ����KBE�Ĳ�����߼�ʵ�壬��KBE���ʵ����ǰ�����Ѿ�������һЩ���������¼�
		// ��˴�ʱ���ǿ����Ѿ������һЩ�¼�������ֻ���ڴ˲��ȱ�Ҫ�Ĵ����ˣ� ���磺���ƺ�Ѫ������ֵ
		if (pEntity)
			pEntity->callPropertysSetMethods();
	}
}

void AEntityBase::Destroyed()
{
	Super::Destroyed();

	auto XGameMode = Cast<AMainGameModeBase>(UGameplayStatics::GetGameMode(this));

	if (XGameMode)
	{
		// ���Լ�ע�ᵽAMainGameModeBase������������
		XGameMode->removeGameEntity(this->entityID);
	}
}

void AEntityBase::updateLocation(float DeltaTime)
{
	const FVector& currLocation = GetActorLocation();

	//Direction from Self to targetPos
	FVector vectorDirection = targetLocation - currLocation;

	float deltaSpeed = (moveSpeed * 10.f /*���ڷ���˽ű�moveSpeed�ĵ�λ�����ף�������Ҫת��ΪUE4��λ����*/) * DeltaTime;
	if (vectorDirection.Size() > deltaSpeed)
	{
		//Normalize Vector so it is just a direction
		vectorDirection.Normalize();

		//Move moveSpeed units toward the player, per tick
		SetActorLocation(currLocation + (vectorDirection * deltaSpeed));
	}
	else
	{
		SetActorLocation(targetLocation);
	}

	FaceRotation(targetRotator, DeltaTime);
}

// Called every frame
void AEntityBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!isPlayerCharacter)
	{
		updateLocation(DeltaTime);
	}
}

// Called to bind functionality to input
void AEntityBase::SetupPlayerInputComponent(class UInputComponent* inputComponent)
{
	Super::SetupPlayerInputComponent(inputComponent);

}

void AEntityBase::FaceRotation(FRotator NewRotation, float DeltaTime)
{
	FRotator CurrentRotation = FMath::RInterpTo(GetActorRotation(), NewRotation, DeltaTime, 8.0f);

	Super::FaceRotation(CurrentRotation, DeltaTime);
}

void AEntityBase::setModelID(int modelID)
{
	this->modelID = modelID;

	if (this->modelID == ModelID_Avatar)
	{
		this->createAvatar();
	}
	else
	{
		this->createMonster();
	}
}

void AEntityBase::createAvatar()
{
	//TArray<UActorComponent*> components = this->GetComponents().Array();
	//for (int i = 0; i < components.Num(); i++)
	//{
	//	if (components[i]->GetName() == "Scene")  //����Ѫ��λ��
	//	{
	//		UWidgetComponent* pWidget = (UWidgetComponent*)components[i];
	//		pWidget->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	//	}

	//	if (components[i]->GetName() == "Sphere")	//��������
	//	{
	//		USphereComponent* pSphere = (USphereComponent*)components[i];
	//		pSphere->SetActive(false);
	//		pSphere->SetVisibility(false);
	//	}

	//	if (components[i]->GetName() == "Cone")		//����Բ׶��
	//	{
	//		UStaticMeshComponent* pCone = (UStaticMeshComponent*)components[i];
	//		pCone->SetActive(false);
	//		pCone->SetVisibility(false);
	//	}
	//}
}

void AEntityBase::createMonster()
{
	//USkeletalMeshComponent* SkeletalMesh = this->GetMesh();
	//SkeletalMesh->SetActive(false);
	//SkeletalMesh->SetVisibility(false);
}

