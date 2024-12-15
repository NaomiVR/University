#pragma once

class FRandomizer
{
public:
	uint8 RandomTW = 0;
	uint8 RandomTL = 0;

	float RandomSL = 0;
	uint8 RandomMiSHR = 0;
	uint8 RandomMaSHR = 0;
	float RandomHFL = 0;

	uint8 RandomO = 0;
	float RandomSF = 0;
	uint8 RandomHM = 0;
	float RandomP = 0;
	
	FRandomizer();

	void RandomiseVariables();

private:
	FRandomStream RandomStream;

	void SetRandomisedVariables();
};
