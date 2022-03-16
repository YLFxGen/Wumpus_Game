#include "Wumpus.h"
using namespace std;

Wumpus::Wumpus() {

}

Wumpus::Wumpus(Cave& initCave) {
	position = initCave;
}

Wumpus::~Wumpus() {

}

Cave Wumpus::getPosition() {
	return position;
}

void Wumpus::setPosition(Cave& newCave) {
	position = newCave;
}

