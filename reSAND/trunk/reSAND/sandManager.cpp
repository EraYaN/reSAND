#include "sandManager.h"
#include "dxManager.h"


sandManager::sandManager(void)
{
SAND_TYPE Water = SAND_TYPE(0, 0, 1.0, 0, 1.0);
SAND exSAND = SAND(0.5,1,0);
SAND_TYPES.push_back(Water);
SANDS.push_back(exSAND);

}

vertex* sandManager::sand2vertex(UINT numVertices){
	numVertices = SANDS.size();
	vertex* iV = new vertex( D3DXVECTOR3(0.5, 0.5,0), D3DXVECTOR4(1,1,1,1) );
		
for (unsigned long index=0; index<numVertices; ++index) {
            iV[index] = vertex( D3DXVECTOR3(SANDS.at(index).X,SANDS.at(index).Y,0), D3DXVECTOR4(SAND_TYPES.at(SANDS.at(index).type).R,SAND_TYPES.at(SANDS.at(index).type).G,SAND_TYPES.at(SANDS.at(index).type).B,1) );
		
       }
	return iV;
}

sandManager::~sandManager(void)
{
}
