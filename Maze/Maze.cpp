#include "def.h"


int main() {

    cout << DESIBLECUR;
    int x = 20;
    int y = 20;
    vector<int> playerpos ;

    vector<vector<string>> maps = init(y, x, playerpos);

    showmaze(maps, y, x);
    bool win = false; 

    while (!win) {
    char key = _getch();
    int ycords = 0;
    int xcords = 0;
        switch (key) {
        case 72 :// Up arrow
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

    showmaze(maps,y,x);

    }
    
    

    return 0;
}
