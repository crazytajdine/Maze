#pragma once

#define MOVE_TO_BEGINNING "\033[H"
#define RESET "\033[0m"
#define PLAYER "\033[1;31m"
#define WINFLAG "\033[1;32m"
#define DISIBLECUR "\033[?25l"
#define ENABLECUR "\033[?25h"
#define MOVE_UP_1_LINE "\033[1A"




#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <thread>
#include <chrono>

using namespace std;
using namespace std ::chrono;

const string Init = "@ ";
const string Route = "  ";
const string Wall = "# ";
const string Player = "$ ";
const string Winflag = "W ";
const int zonelight = 2;
const int OPTIONS_COUNT = 2;
vector<string> options = { "Normal mode","Dark mode" };


int distance(vector<int> v1, vector<int> v2) {

	return sqrt(pow((v1[0] - v2[0]), 2) + pow((v1[1] - v2[1]), 2));
}
#include <iostream>
#include <conio.h>


void displayMenu(int selectedOption) {


	if (selectedOption == 0) {
		cout << WINFLAG << "   Normal mode" <<"\r" << RESET << endl;
		cout  << "   DARK mode" << "\r";

	}
	else {
		cout << "   Normal mode" << "\r" <<endl;
		cout << WINFLAG << "   DARK mode" << "\r" << RESET;

	}
	cout << MOVE_UP_1_LINE;
}






void showmaze(vector<vector<string>> maps, int y, int x) {
	cout << MOVE_TO_BEGINNING;
	for (int j = 0; j < y + 2; j++) {
		for (int i = 0; i < x + 2; i++) {
			if (maps[j][i] == Winflag) {
				cout << WINFLAG << maps[j][i] << RESET;
				continue;
			}
			if (maps[j][i] == Player) {
				cout << PLAYER << maps[j][i] << RESET;
				continue;
			}
			cout  << maps[j][i];
		}
		cout << "\r\n";
	}
}
void darkshowmazemode(vector<vector<string>> maps, int y, int x, vector<int> playercords) {
	cout << MOVE_TO_BEGINNING;
	for (int j = 0; j < y + 2; j++) {
		for (int i = 0; i < x + 2; i++) {
			if (distance(playercords, { j,i }) <= zonelight) {
				if (maps[j][i] == Winflag) {
					cout << WINFLAG << maps[j][i] << RESET;
					continue;
				}
				if (maps[j][i] == Player) {
					cout << PLAYER << maps[j][i] << RESET;
					continue;
				}
				cout << maps[j][i];
			}
			else {
				cout << Route;
			}
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
	maps[y + 1] = borders;

	for (int j = 0; j < y; j++) {
		maps[j + 1][0] = Wall;
		maps[j + 1][x + 1] = Wall;
	}
	srand(time(0));
	int ycords = (rand() % y) + 1;
	int xcords = (rand() % x) + 1;
	playercords = { ycords,xcords };



	genmap(maps, ycords, xcords, y, x);


	maps[playercords[0]][playercords[1]] = Player;
	int flagy;
	int flagx;
	int maxdistance = (x + y) / 4 - 1;
	do {

		flagy = rand() % (y)+1;
		flagx = rand() % (x)+1;
	} while (distance(playercords, { flagy,flagx }) <= maxdistance);

	maps[flagy][flagx] = Winflag;
	return maps;
}



bool changemovechar(vector<vector<string>>& maps, vector<int>& playercords, int newy, int newx) {
	if (maps[newy][newx] == Wall) {
		return false;
	}
	if (maps[newy][newx] == Winflag) {
		cout << " You did it !!!"<<endl;
		cout << " press any key for main menu . " << endl;

		maps[playercords[0]][playercords[1]] = Route;
		maps[newy][newx] = Player;
		playercords = { newy,newx };
		return true;
	}
	maps[playercords[0]][playercords[1]] = Route;
	maps[newy][newx] = Player;
	playercords = { newy,newx };
	return false;

}




