// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "AbilitySystemGlobals.h"
#include "Abilities/GameplayAbilityBase.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<URPGAbilitySystemComponent>(TEXT("AbilitySystem"));
	AbilitySystemComponent->SetIsReplicated(true);

	// 创建属性集
	AttributeSet = CreateDefaultSubobject<UCoreAttributeSet>(TEXT("AttributeSet"));

	bAbilitiesInitialized = false;
}

int32 ACharacterBase::GetCharacterLevel() const
{
	return CharacterLevel;
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACharacterBase::AddStartupGameplayAbilities()
{
	check(AbilitySystemComponent);

	if (Role == ROLE_Authority && !bAbilitiesInitialized)
	{
		// 仅在服务器端初始化技能
		for (TSubclassOf<UGameplayAbilityBase>& StartupAbility : GameplayAbilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility, GetCharacterLevel(), INDEX_NONE, this));
		}

		for (TSubclassOf<UGameplayEffect>& GameplayEffect : PassiveGameplayEffects)
		{
			FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
			EffectContext.AddSourceObject(this);

			FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, GetCharacterLevel(), EffectContext);
			if (NewHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
			}
		}

		bAbilitiesInitialized = true;
	}
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//TODO 背包相关初始化

	//技能初始化
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		AddStartupGameplayAbilities();
	}
}

void ACharacterBase::UnPossessed()
{
}

void ACharacterBase::OnRep_Controller()
{
	Super::OnRep_Controller();

	// 这里因为控制器改变了，必须将AS组件上的ActorInfo更新一下
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->RefreshAbilityActorInfo();
	}
}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

float ACharacterBase::GetHealth() const
{
	return AttributeSet->GetHealth();
}

float ACharacterBase::GetMaxHealth() const
{
	return AttributeSet->GetMaxHealth();
}

