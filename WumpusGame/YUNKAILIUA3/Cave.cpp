#include "Cave.h"
using namespace std;

Cave::Cave() {

}

Cave::Cave(int initCaveNum, vector<int> initAdjacentCaveNum, vector<string> initAdjacentCaveDirection) {
	caveNum = initCaveNum;
	adjacentCaveNum = initAdjacentCaveNum;
	adjacentCaveDirection = initAdjacentCaveDirection;
	isPits = false;
	isBats = false;
}

Cave::~Cave() {

}

bool Cave::getIsPits() {
	return isPits;
}

void Cave::setIsPits(bool newIsPits) {
	isPits = newIsPits;
}

bool Cave::getIsBats() {
	return isBats;
}
void Cave::setIsBats(bool newIsBats) {
	isBats = newIsBats;
}

int Cave::getCaveNum() {
	return caveNum;
}

string Cave::getDescription() {
	return description;
}
void Cave::setDescription(string newDescription) {
	description = newDescription;
}

vector<int> Cave::getAdjacentCaveNum() {
	return adjacentCaveNum;
}
vector<string> Cave::getAdjacentCaveDirection() {
	return adjacentCaveDirection;
}
