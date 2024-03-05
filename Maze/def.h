#pragma once

#define MOVE_TO_BEGINNING "\033[H"
#define RESET "\033[0m"
#define PLAYER "\033[1;31m"
#define DESIBLECUR "\033[?25l"
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
using namespace std;

const string Init = "@ ";
const string Route = "  ";
const string Wall = "# ";
const string Player = "$ ";
const string Winflag = "W ";

void showmaze(vector<vector<string>> maps, int y, int x) {
	cout << MOVE_TO_BEGINNING;
	for (int j = 0; j < y + 2; j++) {
		for (int i = 0; i < x + 2; i++) {
			if (maps[j][i] == Player) {
				cout << PLAYER << maps[j][i] << RESET;
				continue;
			}
			cout << maps[j][i];
		}
		cout << "\r\n";
	}
}

void genmap(vector<vector<string>>& maps, int ycords, int xcords, int sizey, int sizex) {

	vector<vector<int>> isee;
	vector<vector<int>> icangoto;
	vector<vector<int>> newroutes;
	bool carvedanotherpath = false;
	isee = {
	   { ycords - 1,xcords},
	   { ycords + 1,xcords},
	   { ycords ,xcords - 1},
	   { ycords,xcords + 1}
	};
	icangoto = {};

	for (vector<int> direction : isee) {
		if (maps[direction[0]][direction[1]] == Init) {
			icangoto.push_back(direction);
		}

	}
	if (icangoto.size() == 0) {

		return;
	}
	int choosenPathindex = rand() % icangoto.size();
	ycords = icangoto[choosenPathindex][0];
	xcords = icangoto[choosenPathindex][1];
	newroutes.push_back(icangoto[choosenPathindex]);
	maps[ycords][xcords] = Route;


	icangoto.erase(icangoto.begin() + choosenPathindex);
	for (auto spot : icangoto) {

		if (!carvedanotherpath && rand() % 10 == 0) {

			maps[spot[0]][spot[1]] = Route;
			carvedanotherpath = true;
			newroutes.push_back(spot);
		}
		else {


			maps[spot[0]][spot[1]] = Wall;

		}
	}
	for (vector<int> newroute : newroutes) {

		genmap(maps, newroute[0], newroute[1], sizey, sizex);
	}
	isee = {
{ ycords - 2,xcords},
{ ycords + 2,xcords},
{ ycords ,xcords - 2},
{ ycords,xcords + 2}
	};
	for (vector<int> direction : isee) {
		if ((sizey >= direction[0] && direction[0] >= 0) && (sizex >= direction[1] && direction[1] >= 0)) {
			if (maps[direction[0]][direction[1]] != Init) {
				continue;
			}

			int newy = (direction[0] + ycords) / 2;
			int newx = (direction[1] + xcords) / 2;
			maps[newy][newx] = Route;
			genmap(maps, newy, newx, sizey, sizex);

		}

	}

}


vector<vector<string>> init(int y, int x, vector<int>(&playercords)) {

	vector<vector<string>> maps(y + 2, vector<string>(x + 2, Init));
	vector<string> borders(x + 2, Wall);



	maps[0] = borders;
	maps[x + 1] = borders;

	for (int j = 0; j < y; j++) {
		maps[j + 1][0] = Wall;
		maps[j + 1][x + 1] = Wall;
	}
	srand(time(0));
	int ycords = rand() % (y)+1;
	int xcords = rand() % (x)+1;
	playercords = { ycords,xcords };



	genmap(maps, ycords, xcords, y, x);


	maps[playercords[0]][playercords[1]] = Player;
	int flagy;
		int flagx;
	do {

	 flagy = rand() % (y)+1;
	 flagx = rand() % (x)+1;
	} while (sqrt(pow((playercords[0]-flagy),2)+ pow((playercords[1] - flagx),2))<=(x+y)/4);

	maps[flagy][flagx] = Winflag;
	return maps;
}



bool changemovechar(vector<vector<string>>& maps, vector<int>& playercords, int newy, int newx) {
	if (maps[newy][newx] == Wall) {
		return false;
	}
	if (maps[newy][newx] == Winflag) {
		cout << " YOU DID IT !!!!!!!!!!";
		return true;
	}
	maps[playercords[0]][playercords[1]] = Route;
	maps[newy][newx] = Player;
	playercords = { newy,newx };
	return false;

}





