#include "def.h"


int main() {
	cout << DISIBLECUR;
	int selectedOption = 0;
	bool exitmenu = false;
	cout << "hello this is a maze game created by Taj Eddine Marmoul ." << endl;
	cout << "choose type of gameplay :" << endl;
	while (!exitmenu) {
		displayMenu(selectedOption);

		int key = _getch();

		switch (key) {
		case 72:  // Up arrow
			selectedOption = (selectedOption - 1 + options.size()) % options.size();
			break;
		case 80:  // Down arrow
			selectedOption = (selectedOption + 1) % options.size();
			break;

		case 13:  // Enter key
			exitmenu = true;
			break;

		default:
			break;
		}

	}
	system("cls");
	cout << ENABLECUR;
	cout <<  options[selectedOption] << " selected. now choose the size of the maze." << endl;
	cout << "give y (rows): ";
	int y;
	cin >> y;
	cout << "give x (columns): ";
	int x;
	cin >> x;
	system("cls");
	cout << DISIBLECUR;


	vector<int> playerpos;

	vector<vector<string>> maps = init(y, x, playerpos);
	switch (selectedOption)
	{
	case 0 :
		showmaze(maps, y, x);
		break;
	case 1 :
	darkshowmazemode(maps, y, x, playerpos);
	break;
	default:
		break;
	}
	

	bool win = false;

	while (!win) {
		char key = _getch();
		int ycords = 0;
		int xcords = 0;
		switch (key) {
		case 72:// Up arrow
		case 119:  // w
			ycords = -1;
			break;
		case 80:  // Down arrow
		case 115:  // s
			ycords = 1;
			break;
		case 75:  // Left arrow
		case 97:  // a
			xcords = -1;
			break;
		case 77:  // Right arrow
		case 100:  // d
			xcords = 1;
			break;
		}
		win = changemovechar(maps, playerpos, playerpos[0] + ycords, playerpos[1] + xcords);

		switch (selectedOption)
		{
		case 0:
			showmaze(maps, y, x);
			break;
		case 1:
			darkshowmazemode(maps, y, x, playerpos);
			break;
		default:
			break;
		}

	}


	char key = _getch();
	system("cls");
	return main();
}
