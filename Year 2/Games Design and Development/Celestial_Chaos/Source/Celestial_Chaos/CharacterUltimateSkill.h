// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterUltimateSkill.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CELESTIAL_CHAOS_API UCharacterUltimateSkill : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterUltimateSkill();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Skill")
	float Cooldown;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Skill")
	float ActivationTime;

	UFUNCTION(BlueprintCallable)
	void UseSkill();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float TimeSinceLastUse;
};
