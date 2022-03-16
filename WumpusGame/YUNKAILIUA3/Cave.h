#ifndef CAVE_H
#define CAVE_H
#include <string>
#include <vector>
using namespace std;

class Cave {
private:
	int caveNum;                     //Name of the cave
	string description;              //description of the cave
	bool isPits;                     //whether this cave contains pits
	bool isBats;                     //whether this cave contains bats
	vector<int> adjacentCaveNum;     //Hold three adjacent caves' names
	vector<string> adjacentCaveDirection;   //hold the direction of how to move to adjacent caves
	//adjacentCaveDirection[n] holds the direction for moving to adjacentCaveNum[n]
public:
	/*constructors, destructors, setter and getter*/
	Cave();              
	Cave(int initCaveNum, vector<int> initAdjacentCaveNum, vector<string> initAdjacentCaveDirection);
	~Cave();
	bool getIsPits();
	void setIsPits(bool newIsPits);
	bool getIsBats();
	void setIsBats(bool newIsBats);
	int getCaveNum();
	string getDescription();
	void setDescription(string newDescription);
	vector<int> getAdjacentCaveNum();
	vector<string> getAdjacentCaveDirection();
};
#endif // !CAVE_H

