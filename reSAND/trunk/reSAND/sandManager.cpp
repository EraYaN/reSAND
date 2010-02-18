#ifndef SANDMANAGER_H
#define SANDMANAGER_H
 
#include "sandManager.h"


sandManager::sandManager(void)
{
SAND_TYPE Sand = SAND_TYPE(1.0, 0.6, 0.2, 0, 1.0);
SAND_TYPE Water = SAND_TYPE(0.2, 0.2, 1.0, 0, 1.0);
SAND_TYPES.push_back(Water);
SAND_TYPES.push_back(Sand);
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

sandManager::~sandManager(void)
{
}
#endif