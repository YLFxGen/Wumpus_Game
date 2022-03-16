#ifndef WUMPUS_H
#define WUMPUS_H
#include "Cave.h"
using namespace std;

class Wumpus {
private:
	Cave position;          //Wumpus' position
public:
	/*Constructor, destructor, getter and setter*/
	Wumpus();
	Wumpus(Cave& initCave);
	~Wumpus();
	Cave getPosition();
	void setPosition(Cave& newCave);
};
#endif // !WUMPUS_H

