#ifndef SANDMANAGER_H
#define SANDMANAGER_H
 
#include "sandManager.h"


sandManager::sandManager(void)
{
//water
SAND_TYPE Water = SAND_TYPE(0.2, 0.2, 1.0, 0, 1.0);
SAND_TYPES.push_back(Water);
//sand
SAND_TYPE Sand = SAND_TYPE(0.8, 0.6, 0.4, 0, 1.5);
SAND_TYPES.push_back(Sand);
//water
SAND_TYPE Fire = SAND_TYPE(0.8, 0.0, 0.0, 2, -2.5);
SAND_TYPES.push_back(Fire);
//sand
SAND_TYPE Stone = SAND_TYPE(0.4, 0.4, 0.4, 0, 3.0);
SAND_TYPES.push_back(Stone);
/*for(int i=0; i<200; ++i){
	int extra = rand()%2-rand()%-2;
	int extra2 = rand()%2-rand()%-2;
	if(extra==0) extra = 1;
	if(extra==0) extra2 = -1;
	SANDS.push_back(SAND((float)rand()/(float)RAND_MAX*extra,
(float)rand()/(float)RAND_MAX*extra2,0)
);

}*/
/*for(int i=0; i<10; ++i){
	SANDS.push_back(SAND(i*0.5,i*0.5,0));
}*/
}

/*vertex* sandManager::sand2vertex(){
	UINT numVertices = SANDS.size();
	vertex* iV = new vertex;
	for (unsigned long index=0; index<numVertices; ++index) {
    	iV[index] = vertex( D3DXVECTOR3(SANDS.at(index).X,
										SANDS.at(index).Y,
										0),
							D3DXVECTOR4(SAND_TYPES.at(SANDS.at(index).type).R,
										SAND_TYPES.at(SANDS.at(index).type).G,
										SAND_TYPES.at(SANDS.at(index).type).B,
										1)
							);		
    }
	return iV;
}*/
/*UINT sandManager::getNumberOfSands(void){
	return SANDS.size();
}*/
void sandManager::calc_phys(float smallest_unit_x, float smallest_unit_y){
for(UINT i = 0; i<SANDS.size(); ++i){
		float iX,iY; //initial value
		float nX,nY; //new value
		iX = SANDS.at(i).X;
		iY = SANDS.at(i).Y;
		nX = iX;// + (smallest_unit_x*(rand()%SAND_TYPES.at(SANDS.at(i).type).phase*(rand%2-rand%2)))/20;
		nY = iY + (smallest_unit_y*-SAND_TYPES.at(SANDS.at(i).type).weight)/5;
		SANDS.at(i).X = nX;
		SANDS.at(i).Y = nY;
		if(SANDS.at(i).Y< -10 || SANDS.at(i).Y> 10){
			SANDS.erase(SANDS.begin()+i);
		}
		if(SANDS.at(i).X< -10 || SANDS.at(i).X> 10){
			SANDS.erase(SANDS.begin()+i);
		}
	}
}
sandManager::~sandManager(void)
{
}
#endif