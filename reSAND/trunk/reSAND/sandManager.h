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
	int X,Y; //Position
	int type; //index of SAND_TYPES vector

	SAND( int iX, int iY, int iType)
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
private:
	std::vector<SAND_TYPE> SAND_TYPES;
	std::vector<SAND> SANDS;
	
public:
	
	sandManager(void);
	vertex*& sand2vertex(UINT numVertices);
	~sandManager(void);
};

