#pragma once
/**************************
SAND class header
i prefix stands for "initial"

***************************/
#include <windows.h>
#include <vector>
#include "dxManager.h"

//SAND particle types ex. Water, Stone
struct SAND_TYPE
{

float R, G, B;//Rood, Groen, Blauw 0 tot 1
int phase; // solid(0)|liquid(1)|gas(2)
float weight; //gewicht 1 = water

	SAND_TYPE( float iR, float iG, float iB, int iPhase, float iWeight)
	{
		R = iR;
		G = iG;
		B = iB;
		phase = iPhase;
		weight = iWeight;
	}
	SAND_TYPE(void){

	}
	
};
//SAND struct used for every patricle
struct SAND
{
	float X,Y; //Position
	int type; //index of SAND_TYPES vector

	SAND( float iX, float iY, int iType)
	{
		X = iX;
		Y = iY;
		type = iType;
	}
	SAND(void){

	}

};

class sandManager
{

	
public:
	std::vector<SAND_TYPE> SAND_TYPES;
	std::vector<SAND> SANDS;
	sandManager(void);
	/*******
	Physics
	*******/
	void calc_phys(float smallest_unit_x, float smallest_unit_y);

	//vertex* sand2vertex(void);
	//UINT getNumberOfSands();
	~sandManager(void);
};

