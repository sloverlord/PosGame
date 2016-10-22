#include<iostream>
#include<string.h>

#include"movement.cpp"

int main (void){
	person *player = new person();
	std::string dir = "up";
	
	// makes stuff for rooms
	f1.field[1][1] = 9; // obstacle
	f1.field[4][0] = 6; // healing
	f1.field[0][4] = 5; // npc
	
	field = f1;
	
	field.field[player->getX()][player->getY()] = 1;
	
	// reads input to move the charachter with below directions
	while (std::cin >> dir){
		if (dir == "w"){
			move(player, player->getLoc()+point(-1,0));
		} else if (dir == "s"){
			move(player, player->getLoc()+point(1,0));
		} else if (dir == "a"){
			move(player, player->getLoc()+point(0,-1));
		} else if (dir == "d"){
			move(player, player->getLoc()+point(0,1));
		}
		
		printBoard(WIDTH, HEIGHT);
	}
}
