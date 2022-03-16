#include "Player.h"
using namespace std;

Player::Player() {

}

Player::~Player() {

}

void Player::setName(string newName) {
	name = newName;
}

string Player::getName() {
	return name;
}

Cave Player::getPosition() {
	return position;
}

void Player::setPosition(Cave& newPosition) {
	position = newPosition;
}