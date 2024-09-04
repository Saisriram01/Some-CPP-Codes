#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <cstdlib> // For rand()

using namespace std;

// Global variables
int score;
const int width = 30, height = 15; // Adjusted width and height
bool gameover;
int x, y, food_x, food_y;
namespace game {
    enum direction { stop, left, right, top, down };
}   
game::direction dir;

// Save the original terminal settings
struct termios orig_termios;
void saveOriginalSettings() {
    tcgetattr(STDIN_FILENO, &orig_termios);
}

void restoreOriginalSettings() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

// Function to set non-blocking input
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

// Function to check for keypress
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
            else
                cout << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < width; i++)
        cout << "#";
    cout << endl;
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

    // Check for boundaries
    if (x >= width - 1 || x < 1 || y >= height - 1 || y < -1) {
        gameover = true;
    }

    // Check if the snake eats the food
    if (x == food_x && y == food_y) {
        score += 10;
        food_x = rand() % (width - 2) + 1;
        food_y = rand() % (height - 2) + 1;
    }
}

int main() {
    saveOriginalSettings();
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
    restoreOriginalSettings(); // Restore original terminal settings
    cout << "Game Over! Your score: " << score << endl;
    return 0;
}
