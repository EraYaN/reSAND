#include "sandManager.h"
#include "dxManager.h"



sandManager::sandManager(void)
{
SAND_TYPE Water = SAND_TYPE(0, 0, 1.0, 0, 1.0);
SAND exSAND = SAND(0.5,1,0);
SAND ex2SAND = SAND(0.6,1,0);
SAND_TYPES.push_back(Water);
SANDS.push_back(exSAND);
SANDS.push_back(ex2SAND);

}

vertex* sandManager::sand2vertex(){
	UINT numVertices = SANDS.size();
	vertex* iV = new vertex( D3DXVECTOR3(0.5, 0.5,0), D3DXVECTOR4(1,1,1,1) );
		
/*for (unsigned long index=0; index<numVertices; ++index) {
           

 iV[index] = vertex( D3DXVECTOR3(SANDS.at(index).X,SANDS.at(index).Y,0), D3DXVECTOR4(SAND_TYPES.at(SANDS.at(index).type).R,SAND_TYPES.at(SANDS.at(index).type).G,SAND_TYPES.at(SANDS.at(index).type).B,1) );
		
       }*/

	   	//lock vertex buffer for CPU use
vertex* v = NULL;
	dx.pVertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, (void**) &v );
	
	for(unsigned int index = 0;index<numVertices;++index){
		v[index] = vertex( D3DXVECTOR3(SANDS.at(index).X,SANDS.at(index).Y,0), D3DXVECTOR4(SAND_TYPES.at(SANDS.at(index).type).R,SAND_TYPES.at(SANDS.at(index).type).G,SAND_TYPES.at(SANDS.at(index).type).B,1) );

	}
	dx.pVertexBuffer->Unmap();
	return iV;
}
UINT sandManager::getNumberOfSands(){
	return SANDS.size();
}
sandManager::~sandManager(void)
{
}
