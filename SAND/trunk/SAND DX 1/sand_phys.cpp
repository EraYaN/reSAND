#include "sand_phys.h"
#include "main.h"

SAND start_sands = {100,100,1};
SAND_TYPE Water = {0.0f,0.0f,255.0f,3,1.0f};


sand_phys::sand_phys()
{
	sands.push_back(start_sands);
}


sand_phys::~sand_phys(void)
{

}

int sand_phys::calculate(float xPos, float yPos, float &newXpos, float &newYpos, int sand_id)
{
int phasemax, phasemin;
//dwarreligheid...
switch(sand_types.at(sands.at(sand_id).type).phase)
{
	case 0:		
		phasemax = 2;
		phasemin = 0;
		break;
	case 1:
		phasemax = 5;
		phasemin = 2;
		break;
	case 2:
		phasemax = 10;
		phasemin = 3;
		break;
	default:
		phasemax = 1;
		phasemin = 0;
}

float yForce = (sand_types.at(sands.at(sand_id).type).weight*-9.81)+sands.at(sand_id).Y_Force;
float xForce = (rand()%phasemax+phasemin)+sands.at(sand_id).X_Force;
newXpos = xPos+xForce/10;
newYpos = yPos+yForce/10;
return 0;
}
void add_sands_to_vertex(SAND sand_dat){
	CUSTOMVERTEX buffer_vertex = {sand_dat.X,sand_dat.Y,1.0f,1.0f,D3DCOLOR_XRGB(sand_types.at(sand_dat.type).R, sand_types.at(sand_dat.type).G, sand_types.at(sand_dat.type).B)};
	SAND_vertices.push_back(buffer_vertex);

}

