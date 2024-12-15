// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStatsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnXpChanged, float, NewXp);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CELESTIAL_CHAOS_API UCharacterStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterStatsComponent();

	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnXpChanged OnXpChanged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float PickupDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float PassiveHealthRegeneration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float AdditionalSkillDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float Armour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float Defence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float CritChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float Evasion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float CooldownModifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float Experience;

	UFUNCTION(BlueprintCallable)
	void AddXp(float Var);

	UFUNCTION()
	void IncreaseMaxHealth(float Var);
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void PassiveRegen();
};
