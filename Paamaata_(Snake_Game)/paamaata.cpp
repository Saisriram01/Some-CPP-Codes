#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <cstdlib> 

using namespace std;
// global Variables
int score;
const int width = 30, height = 15; 
bool gameover;
int x, y, food_x, food_y;
int x_body[100], y_body[100], len_body = 0;
namespace game {
    enum direction { stop, left, right, top, down };
}   
game::direction dir;


// struct termios orig_termios;
// void saveOriginalSettings() {
//     tcgetattr(STDIN_FILENO, &orig_termios);
// }

// void restoreOriginalSettings() {
//     tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
// }

void setNonBlocking(bool enable) {
    struct termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);

    if (enable) {
        ttystate.c_lflag &= ~ICANON;
        ttystate.c_lflag &= ~ECHO;
        ttystate.c_cc[VMIN] = 1;
    } else {
        ttystate.c_lflag |= ICANON;
        ttystate.c_lflag |= ECHO;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

int _kbhit() {
    struct timeval tv = {0, 0};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
}

void init() {
    gameover = false;
    score = 0;
    x = width / 3;
    y = height / 3;
    dir = game::stop;
    food_x = rand() % (width - 2) + 1;
    food_y = rand() % (height - 2) + 1;
}

void arena() {
    system("clear"); 
    for (int i = 0; i < width; i++)
        cout << "#";
    cout << endl;
    for (int i = 0; i < height - 1; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0 || j == width - 1)
                cout << "#";
            else if (i == y && j == x)
                cout << "O";
            else if (food_y == i && food_x == j)
                cout << "F";
            else{
                bool body_print = false;
                for ( int k = 0; k < len_body; k++)
                {
                    if(x_body[k] == j && y_body[k] == i){
                        cout<<"o";
                        body_print = true;
                    }
                }
                if(!body_print)
                    cout<< " ";

            }
        }
        cout << endl;
    }

    for (int i = 0; i < width; i++)
        cout << "#";
    cout << endl<<"Score: "<<score<<endl;
}

void input() {
    if (_kbhit()) {
        char ch = getchar();
        if (ch == '\033') { // checking for first character ESC
            getchar();      // Skipping the '[' character
            switch (getchar()) { // Getting the actual arrow key
                case 'A':
                    if (dir != game::down) dir = game::top;
                    break;
                case 'B':
                    if (dir != game::top) dir = game::down;
                    break;
                case 'C':
                    if (dir != game::left) dir = game::right;
                    break;
                case 'D':
                    if (dir != game::right) dir = game::left;
                    break;
            }
        }
    }
}

void logic() {

    int prevx = x_body[0];
    int prevy = y_body[0];
    x_body[0] = x;
    y_body[0] = y;
    int prev2x, prev2y;
    for(int i = 1;i < len_body;i++){
        prev2x = x_body[i];
        prev2y = y_body[i];

        x_body[i] = prevx;
        y_body[i] = prevy;

        prevx = prev2x;
        prevy = prev2y;

    }
    switch (dir) {
        case game::left:
            x--;
            break;
        case game::right:
            x++;
            break;
        case game::top:
            y--;
            break;
        case game::down:
            y++;
            break;
    }

    if( x >= width - 1)
        x = 1;
    else if( x < 1)
        x = width - 1;
    else if( y < 0)
        y = height - 1;
    else if( y >= height - 1)
        y = 0;

    for(int i = 1; i < len_body; i++)
        if(x_body[i] == x && y_body[i] == y)
            gameover = true;

    if (x == food_x && y == food_y) {
        score ++;
        food_x = rand() % (width - 2) + 1;
        food_y = rand() % (height - 2) + 1;
        len_body++;
    }
}

int main() {
    // saveOriginalSettings();
    setNonBlocking(true);
    init();

    while (!gameover) {
        arena();
        input();
        logic();
        if(dir == game::left || dir == game::right)
            usleep(55000);
        else 
            usleep(100000); // 100 milliseconds delay
    }

    setNonBlocking(false);
    // restoreOriginalSettings(); 
    cout << "Game Over! Your score: " << score << endl;
    return 0;
}
