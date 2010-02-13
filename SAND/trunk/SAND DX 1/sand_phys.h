#pragma once
struct SAND
{
float X, Y, X_Force, Y_Force; //xPos, yPos, xForce, yForce
int type; //type index
};

struct SAND_TYPE
{
int R, G, B;//Rood , Greon, Blauw
char phase; // solid(0)|liquid(1)|gas(2)
float weight; //gewicht
};
class sand_phys
{
public:
	sand_phys();
	~sand_phys(void);
	int calculate(float xPos, float yPos, float &newXpos, float &newYpos, int sand_id);
	void add_sands_to_vertex(SAND sand_dat);
	
};

