// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Client.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Abilities/RPGAbilitySystemComponent.h"
#include "Abilities/CoreAttributeSet.h"
#include "CharacterBase.generated.h"

class UGameplayAbilityBase;

UCLASS()
class CLIENT_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	virtual void OnRep_Controller() override;

	// Inherited via IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable)
	virtual float GetHealth() const;

	UFUNCTION(BlueprintCallable)
	virtual float GetMaxHealth() const;

	// Implement IAbilitySystemInterface
	UPROPERTY(BlueprintReadOnly)
	URPGAbilitySystemComponent* AbilitySystemComponent;

	UFUNCTION(BlueprintCallable)
	virtual int32 GetCharacterLevel() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Replicated,Category = Abilities)
	int32 CharacterLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Abilities)
	TArray<TSubclassOf<UGameplayAbilityBase>> GameplayAbilities;

	/** ����ʱ Ӧ�� ����Ч�� */
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Abilities)
	TArray<TSubclassOf<UGameplayEffect>> PassiveGameplayEffects;

	UPROPERTY()
	UCoreAttributeSet* AttributeSet;

	/** If true we have initialized our abilities */
	UPROPERTY()
		int32 bAbilitiesInitialized;



	/** Ӧ��Ability��Effect�ĳ�ʼ�� */
	void AddStartupGameplayAbilities();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;




};
