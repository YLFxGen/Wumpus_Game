#include <iostream>
#include <fstream>
#include "Cave.h"
#include "Player.h"
#include "Wumpus.h"
using namespace std;

Cave allCaves[20];                               
Player hunter;
Wumpus monster;
bool isGameEnd = false;
bool isVictory = false;
int oilAmount = 30;
int numArrow = 5;
int numLife = 2;                            // used for additional function, to store how many lives player have
int mapPosition;                            // used for additional function, to store the position of map
bool hasMap = false;                        // used for additional function, to store whether player obtain the map or not

/*This function is used for creating nad initializing 20 cave objects, assigning them with unique name, description
, and adjacent caves. Meanwhile, this function will randomly set bats or pits in caves*/
void initialCave();

/*This function is used for creating and initializing wumpus object, giving it a random initial position*/
void initialMonster();

/*This function is used for creating and initializing player object. This function will ask for player's input 
to initialize player's name and give player a random starting position that is not same as any hazards*/
void initialPlayer();

/*This function is used for achiving MOVE instruction. This function allows player's location to be reset 
according to the parameter and provides player with all neccessary information to ensure that player know
what they can do next. If player meet any hazards, program will decide whether game needs to be ended or not*/
void goSomewhere(string direction); 

/*This function is used for reading in text from txt file*/
void openDocument(string documentOpened);

/*This function is used for achiving SHOOT instruction. This function allows player to attack wumpus. Parameter is
used for deciding the direction of arrow. If arrow goes to the correct direction, player will win. Otherwise, this
function will decide whether wumpus will move or not.*/
void shoot(string direction);

/*This function is used for displaying hazards description if there are any hazards surrounding the player*/
void showSurroundingHazards();

/*This function is used for resetting player's position to a random cave and dispalying all neccessary 
information to ensure that player know what they can do next. This function will make sure that player's
new position is not same as any hazards*/
void resetPosition();

int main() {
	// display splash screen
	openDocument("background");
	system("pause");
	system("cls");
	openDocument("howToPlay");
	system("pause");
	system("cls");
	openDocument("victoryCondition");
	system("pause");
	system("cls");
	openDocument("helpMenu");
	system("pause");
	system("cls");
	//Initialize all game assets
	initialCave();
	initialMonster();
	initialPlayer();
	//If game does not come to an end, this loop will continue running to ask for player's instruction
	while (!isGameEnd) {
		string instruction;
		string verb;
		string direction;
		cout << "\nWhat now?" << endl;
		getline(cin, instruction);                          //get user input
		int spaceIndex = instruction.find(" ");
		if (spaceIndex == string::npos) {                   //find whether the instruction contains two words      
			verb = instruction;
			direction = "";
		}
		else {
			/*Take verb as conditions for deciding which function needs to be run and take direction
			as parameter*/
			verb = instruction.substr(0, spaceIndex);            
			direction = instruction.substr(spaceIndex + 1);
		}
		if (verb == "MOVE") {
			goSomewhere(direction);
		}
		else if (verb == "SHOOT") {
			shoot(direction);
		}
		/*---------------Additional feature---------------*/
		else if (verb == "MAP" && direction == "") {
			if(hasMap){ 
				openDocument("map"); 
			}
			else {
				cout << "You do not have map on you" << endl;
			}
		}
		/*------------------------------------------------*/
		else {
			cout << "Please enter a valid instruction" << endl;
		}
		oilAmount--;                             //Each turn reduce amount of oil by one
		if (oilAmount == 0) {
			isGameEnd = true;
			isVictory = false;
		}
	}
	if (isVictory) {
		cout << "You win!" << endl;
	}
	else {
		cout << "You lose!" << endl;
	}

	system("pause");
	return 0;
}

void initialCave() {
	string caveName[20];
	string caveDescription[20];
	/*Use two arrays to hold each cave's adjacent caves information. Every three elements is for one cave.
	For example, player can move N, E, W to cave 2, 2, 13 from cave 1*/
	int allAdjacentCaveNum[] = {2,2,13,1,5,1,4,7,6,5,8,3,2,9,4,3,7,10,3,11,6,4,9,12,5,12,8,6,11,13,7,
		12,10,8,9,11,10,14,1,15,15,13,16,14,14,17,18,15,19,19,16,20,20,16,17,20,17,19,18,18};
	
	string allAdjacentCaveDirection[] = {"N","E","W","N","E","W","E","S","W","E","S","W","N","S","W","N"
	,"E","S","N","S","W","N","E","S","N","S","W","N","E","S","N","E","W","N","E","W","N","E","W","E","S",
	"W","E","S","W","N","E","W","N","E","W","E","S","W","N","E","W","E","S","W"};

	int start = 0;
	ifstream initCaveName;
	initCaveName.open("caveName.txt");
	for (int i = 0; i < 20;i++) {
		/*using three elements from arrays to create and initialize a cave object*/
		vector<int> eachCaveAdjacentCaveNum = { allAdjacentCaveNum[start],
			allAdjacentCaveNum[start + 1],allAdjacentCaveNum[start + 2] };

		vector<string> eachCaveAdjacentCaveDirection = { allAdjacentCaveDirection[start],
			allAdjacentCaveDirection[start + 1],allAdjacentCaveDirection[start + 2] };

		allCaves[i] = Cave(i + 1, eachCaveAdjacentCaveNum, eachCaveAdjacentCaveDirection);
		start += 3;
		if (initCaveName.is_open()) {
			initCaveName >> caveName[i];
		}
		else {
			cout << "File does not exist" << endl;
		}
		ifstream initCaveDescription;
		string line;
		initCaveDescription.open(caveName[i]+".txt");
		if (initCaveDescription.is_open()) {
			while (getline(initCaveDescription, line)) {               //get name and description from files
				 caveDescription[i] += line + "\n";
			}
			allCaves[i].setDescription(caveDescription[i]);
		}
		else {
			cout << "File does not exist" << endl;
		}
		initCaveDescription.close();
	}
	initCaveName.close();
	/*Get several random value, and use these values to set bats,pits and map into caves*/
	int randValueA = 0;                 
	int randValueB = 0;
	int randValueC = 0;
	int randValueD = 0;
	int randValueE = rand() % 20;
	int randValueF = rand() % 20;
	do
	{
		randValueA = rand() % 20;
		randValueB = rand() % 20;
	} while (randValueA == randValueB);
	allCaves[randValueA].setIsPits(true);
	allCaves[randValueB].setIsPits(true);
	do
	{
		randValueC = rand() % 20;
		randValueD = rand() % 20;
	} while (randValueC == randValueD);
	allCaves[randValueC].setIsBats(true);
	allCaves[randValueD].setIsBats(true);
	mapPosition = randValueE;
}

void initialPlayer() {
	string playerName;
	cout << "Please enter your name:" << endl;
	cin >> playerName;
	hunter.setName(playerName);
	cout << "Hi, " << hunter.getName() << "! Ready to begin the game?" << endl;
	cin.ignore(1024, '\n');                                 //clear cin to be ready for receiving next instruction
	system("pause");
	system("cls");
	resetPosition();                                        //set player's initial position
	
}

void initialMonster() {
	int randValue = rand() % 20;
	Cave& monsterPosition = allCaves[randValue];
	monster.setPosition(monsterPosition);
}


void shoot(string direction) {
	int destination = -1;

	for (int i = 0;i < 3;i++) {
		if (direction == hunter.getPosition().getAdjacentCaveDirection()[i]) {
			/*To know which cave corresponds to the direction*/
			destination = hunter.getPosition().getAdjacentCaveNum()[i];    
		}
	}

	if (destination > 0) {        // destination > 0, user enter a valid direction. If user input is invalid, destination = -1
		/*To decide whether player shoot the wumpus*/
		if (allCaves[destination - 1].getCaveNum() == monster.getPosition().getCaveNum()) {
			isGameEnd = true;
			isVictory = true;
			cout << "You killed wumpus" << endl;
		}
		else {
			cout << "You missed target" << endl;
			numArrow--;
			/*If player run out of arrows, game ends*/
			if (numArrow == 0) {
				cout << "You have run out of arrow" << endl;
				isGameEnd = true;
				isVictory = false;
			}
			else {
				cout << "You make some noise. Wumpus may move" << endl;
				/*Get a random value from 0 to 99. If value >= 75, monster will move randomly to an adjacent cave*/
				int randVal = rand() % 100;
				if (randVal >= 75) {
					int randDirection = rand() % 3;
					Cave& monsNewPosition = allCaves[monster.getPosition().getAdjacentCaveNum()[randDirection] - 1];
					monster.setPosition(monsNewPosition);
					/*If wumpus move to the same cave as player, player lose*/
					if (monster.getPosition().getCaveNum() == hunter.getPosition().getCaveNum()) {
						cout << "You become wumpus' lunch" << endl;
						/*----------Additional feature----------*/
						/*Player have two lives. After player meet hazards, number of lives will reduce and 
						player will be reset to a new position that is not same as any hazards*/
						numLife--;
						if (numLife == 0) {
							isGameEnd = true;
							isVictory = false;
						}
						else {
							cout << "You lost one life" << endl;
							resetPosition();
						}
						/*--------------------------------------*/
					}
				}
			}
		}
	}
	else {
		cout << "Please enter a valid direction!" << endl;
	}
}

void goSomewhere(string direction) {
	int destination = -1;

	for (int i = 0;i < 3;i++) {
		/*To know which cave corresponds to the direction*/
		if (direction == hunter.getPosition().getAdjacentCaveDirection()[i]) {
			destination = hunter.getPosition().getAdjacentCaveNum()[i];
		}
	}

	if (destination > 0) {// destination > 0, user enter a valid direction. If user input is invalid, destination = -1
		Cave& currentLocation = allCaves[destination - 1];
		hunter.setPosition(currentLocation);// change player's location to new cave
		if (hunter.getPosition().getIsPits()) {   // check whether player meet bottomless pits
			cout << "You fall into bottomless pits" << endl;
			numLife--;
			if (numLife == 0) {
				isGameEnd = true;
				isVictory = false;
			}
			else {
				cout << "You lost one life" << endl;
				resetPosition();
			}
		}
		else {
			if (hunter.getPosition().getIsBats()) {  //check whether player meet bats
				cout << "You are carried away by bats" << endl;
				int randNum = rand() % 20;
				Cave& newPos = allCaves[randNum];
				hunter.setPosition(newPos);	       //reset player's location to a random cave
				/*Check whether player's new position is same as any hazards and display suitable information*/
				if (monster.getPosition().getCaveNum() == hunter.getPosition().getCaveNum()) {
					cout << "You become wumpus' lunch" << endl;
					numLife--;
					if (numLife == 0) {
						isGameEnd = true;
						isVictory = false;
					}
					else {
						cout << "You lost one life" << endl;
						resetPosition();
					}
				}
				else if (hunter.getPosition().getIsPits()) {
					cout << "You fall into bottomless pits" << endl;
					numLife--;
					if (numLife == 0) {
						isGameEnd = true;
						isVictory = false;
					}
					else {
						cout << "You lost one life" << endl;
						resetPosition();
					}
				}
				else {
					/*Additional feature*/
					//If player's position is same as map, player get the map and then can use MAP instruction
					if (hunter.getPosition().getCaveNum() == mapPosition) {
						cout << "You pick up a [map] of this cavern" << endl;
						hasMap = true;
						mapPosition = -1;
					}
					/*------------------*/
					cout << hunter.getPosition().getDescription() << endl;
					cout << "You can move to: " << endl;
					for (int i = 0;i < 3;i++) {
						cout << "Cave " << hunter.getPosition().getAdjacentCaveNum()[i] << ":"
							<< hunter.getPosition().getAdjacentCaveDirection()[i] << endl;
					}
					showSurroundingHazards();
				}
			}
			else {
				if (monster.getPosition().getCaveNum() == hunter.getPosition().getCaveNum()) {
					cout << "You become wumpus' lunch" << endl;
					numLife--;
					if (numLife == 0) {
						isGameEnd = true;
						isVictory = false;
					}
					else {
						cout << "You lost one life" << endl;
						resetPosition();
					}
				}
				else {
					if (hunter.getPosition().getCaveNum() == mapPosition) {
						cout << "You pick up a [map] of this cavern" << endl;
						hasMap = true;
						mapPosition = -1;
					}
					cout << hunter.getPosition().getDescription() << endl;
					cout << "You can move to: " << endl;
					for (int i = 0;i < 3;i++) {
						cout << "Cave " << hunter.getPosition().getAdjacentCaveNum()[i] << ":"
							<< hunter.getPosition().getAdjacentCaveDirection()[i] << endl;
					}
					showSurroundingHazards();
				}
			}
		}
	}
	else {
		cout << "Please enter a valid direction!" << endl;
	}
}

void showSurroundingHazards() {
	bool isPrintAlertP = false;   //check whether there are caves containing pits surrounding
	for (int i = 0;i < 3;i++) {
		if (allCaves[hunter.getPosition().getAdjacentCaveNum()[i] - 1].getIsPits()) {
			isPrintAlertP = true;
		}
	}
	if (isPrintAlertP) {
		openDocument("bottomlessPits");
	}
	bool isPrintAlertB = false;   //check whether there are caves containing bats surrounding
	for (int i = 0;i < 3;i++) {
		if (allCaves[hunter.getPosition().getAdjacentCaveNum()[i] - 1].getIsBats()) {
			isPrintAlertB = true;
		}
	}
	if (isPrintAlertB) {
		openDocument("bats");
	}
	bool isPrintAlertW = false;   //check whether there are caves containing wumpus surrounding
	for (int i = 0;i < 3;i++) {
		if (allCaves[hunter.getPosition().getAdjacentCaveNum()[i] - 1].getCaveNum() ==
			monster.getPosition().getCaveNum()) {
			isPrintAlertW = true;
		}
	}
	if (isPrintAlertW) {
		openDocument("wumpus");
	}
}

void openDocument(string documentOpened) {
	string line;
	ifstream doc;
	doc.open(documentOpened + ".txt");
	if (doc.is_open()) {
		while (getline(doc, line)) {
			cout << line << endl;
		}
	}
	else {
		cout << "File doesn't exist!" << endl;
	}
	doc.close();
}

void resetPosition() {
	/*Get a random value from 0 to 19. Use this value to set player's position. If player's
	position is same as any hazards, get a new random value and reset player's position again*/
	do
	{
		int randValue = rand() % 20;
		Cave& startingPoint = allCaves[randValue];
		hunter.setPosition(startingPoint);
	} while (hunter.getPosition().getIsPits() || hunter.getPosition().getCaveNum() == monster.getPosition().getCaveNum()
		|| hunter.getPosition().getIsBats());
	/*Show neccessary information to ensure that player know what they can do next*/
	cout << hunter.getPosition().getDescription() << endl;
	cout << "You can move to: " << endl;
	for (int i = 0;i < 3;i++) {
		cout << "Cave " << hunter.getPosition().getAdjacentCaveNum()[i] << ":"
			<< hunter.getPosition().getAdjacentCaveDirection()[i] << endl;
	}
	showSurroundingHazards();
}
