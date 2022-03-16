#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "Cave.h"
using namespace std;
class Player {
private:
	string name;        //Player's name 
	Cave position;      //Player's position
public:
	/*Constructor, destructor, getter and setter*/
	Player();
	~Player();
	void setName(string newName);
	string getName();
	Cave getPosition();
	void setPosition(Cave& newCave);
};

#endif // !PLAYER_H

