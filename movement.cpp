#include<iostream>
#include<string.h>

#include"game.h"

void printBoard(int xSize, int ySize){
	for (int i = 0; i < xSize; i += 1){
		for (int j = 0; j < ySize; j += 1){
			if (field.field[i][j] == 0){
				std::cout << ". ";
			} else { std::cout << field.field[i][j] << " "; }
		}
		
		std::cout << std::endl;
	}
}

// checks if given point is on the board
bool onBoard(point dest){
	if (dest.a >= HEIGHT){
		return false;
	}
	
	if (dest.a < 0){
		return false;
	}
	
	if (dest.b >= WIDTH){
		return false;
	}
	
	if (dest.b < 0){
		return false;
	}
	
	return true;
}

// moves passed in moveMe to passed in point dest and updates the board
void move (person *moveMe, point dest){
	// move to a new "room" will need overhaul for multiple rooms
	if (onBoard(dest) && field.field[dest.a][dest.b] == 7){
		if (field.getId() == 1){
			field.field[moveMe->getX()][moveMe->getY()] = 0;
			dest = f2.getDoor().getDest();
			f1 = field;
			field = f2;
			moveMe->move(dest);
			field.field[dest.a][dest.b] = 1;
		} else if (field.getId() == 2){
			field.field[moveMe->getX()][moveMe->getY()] = 0;
			dest = f1.getDoor().getDest();
			f2 = field;
			field = f1;
			moveMe->move(dest);
			field.field[dest.a][dest.b] = 1;
		}
	} else if (onBoard(dest) && field.field[dest.a][dest.b] == 6){
		moveMe->giveHp(1);
	} else if (onBoard(dest) && field.field[dest.a][dest.b] == 0){
		field.field[moveMe->getX()][moveMe->getY()] = 0;
		moveMe->move(dest);
		field.field[dest.a][dest.b] = 1;
	}
	
	std::cout << "Hp: " << moveMe->getHp() << std::endl;
}
