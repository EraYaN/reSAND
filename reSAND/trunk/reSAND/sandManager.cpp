#ifndef SANDMANAGER_H
#define SANDMANAGER_H
 
#include "sandManager.h"


sandManager::sandManager(void)
{
SAND_TYPE Water = SAND_TYPE(0, 0, 1.0, 0, 1.0);
SAND exSAND = SAND(0.5,1,0);
SAND ex2SAND = SAND(0.7,1,0);
SAND_TYPES.push_back(Water);
SANDS.push_back(exSAND);
SANDS.push_back(ex2SAND);

}

vertex* sandManager::sand2vertex(){
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
}
UINT sandManager::getNumberOfSands(void){
	return SANDS.size();
}

sandManager::~sandManager(void)
{
}
#endif