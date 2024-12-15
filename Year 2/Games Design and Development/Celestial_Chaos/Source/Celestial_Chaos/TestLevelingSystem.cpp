// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLevelingSystem.h"

// Sets default values for this component's properties
UTestLevelingSystem::UTestLevelingSystem()
{
}


int32 UTestLevelingSystem::ExperienceIncrement()
{
	NewExperienceLimit = 500 * (Level * Level) - (500 * Level);

	return NewExperienceLimit;
}


int32 UTestLevelingSystem::LevelUp()
{
	if (Experience > NewExperienceLimit)
	{
		Level += 1;
	}

	return Level;
}
