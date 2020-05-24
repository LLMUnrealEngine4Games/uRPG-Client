// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilities//RPGAbilitySystemComponent.h"
#include "EntityBase.generated.h"

const int ModelID_NPC = 1002;
const int ModelID_Monster1 = 1003;
const int ModelID_Monster2 = 1004;
const int ModelID_Gate = 40001001;
const int ModelID_Avatar = 90000001;

UCLASS()
class CLIENT_API AEntityBase : public ACharacter//, public IAbilitySystemInterface
{
	GENERATED_UCLASS_BODY()

public:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called once this actor has been deleted */
	virtual void Destroyed() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* inputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
		virtual void FaceRotation(FRotator NewRotation, float DeltaTime = 0.f) override;

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
		void updateLocation(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
		void setTargetLocation(const FVector& loc)
	{
		targetLocation = loc;
	}

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
		void setTargetRotator(const FRotator& rot)
	{
		targetRotator = rot;
	}

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
		void setIsOnGround(bool onGround)
	{
		isOnGround = onGround;
	}

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
		virtual void setModelID(int modelID);

	//UFUNCTION(BlueprintCallable, Category = "KBEngine")
	//	virtual bool isPlayer() {
	//	return false;
	//}

private:
	void createAvatar();
	void createMonster();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
		float modelScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
		int modelID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
		float moveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
		int entityID;

	// ʵ�彫Ҫ�ƶ�����Ŀ�ĵ�λ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
		FVector targetLocation;

	// ʵ�彫Ҫ�ƶ�����Ŀ�ĳ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
		FRotator targetRotator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
		bool isOnGround;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KBEngine)
		bool isPlayerCharacter;

	// Implement IAbilitySystemInterface
	//UPROPERTY()
	//URPGAbilitySystemComponent* AbilitySystemComponent;

};
