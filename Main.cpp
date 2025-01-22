#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

const int SCREEN_SIZE_X = 10;
const int SCREEN_SIZE_Y = 20;

int field[SCREEN_SIZE_Y][SCREEN_SIZE_X];
int score = 0;

int currentX = SCREEN_SIZE_X / 2 - 2;
int currentY = 0;
int currentRotation = 0;
int currentShape[4][4];
//Prototypes
void createShape();
//
int shapes[7][4][4] = {
    {
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {1, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    {
        {0, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }
};

void rotateShape() {
    int tempShape[4][4];
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            tempShape[i][j] = currentShape[3 - j][i];
        }
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            currentShape[i][j] = tempShape[i][j];
        }
    }
}

bool isCanMove() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (currentShape[i][j]) {
                int x = currentX + j;
                int y = currentY + i;
                if (x < 0 || x >= SCREEN_SIZE_X || y >= SCREEN_SIZE_Y || (y >= 0 && field[y][x])) {
                    return false;
                }
            }
        }
    }
    return true;
}

void placeShape() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (currentShape[i][j]) {
                int x = currentX + j;
                int y = currentY + i;
                if (y >= 0) field[y][x] = 1;
            }
        }
    }
}

void clearLines() {
    for (int i = SCREEN_SIZE_Y - 1; i >= 0; --i) {
        bool fullLine = true;
        for (int j = 0; j < SCREEN_SIZE_X; ++j) {
            if (field[i][j] == 0) {
                fullLine = false;
                break;
            }
        }
        if (fullLine) {
            score += 100;
            for (int k = i; k > 0; --k) {
                for (int j = 0; j < SCREEN_SIZE_X; ++j) {
                    field[k][j] = field[k - 1][j];
                }
            }
            for (int j = 0; j < SCREEN_SIZE_X; ++j) {
                field[0][j] = 0;
            }
            ++i;
        }
    }
}

void drawScreen() {
    system("cls");
    for (int i = 0; i < SCREEN_SIZE_Y; ++i) {
        for (int j = 0; j < SCREEN_SIZE_X; ++j) {
            if (field[i][j] == 0) {
                bool isPartOfShape = false;
                for (int k = 0; k < 4; ++k) {
                    for (int l = 0; l < 4; ++l) {
                        if (currentShape[k][l]) {
                            int x = currentX + l;
                            int y = currentY + k;
                            if (x == j && y == i) {
                                isPartOfShape = true;
                                break;
                            }
                        }
                    }
                    if (isPartOfShape) break;
                }

                if (isPartOfShape) {
                    cout << "#";
                } else {
                    cout << ".";
                }
            } else {
                cout << "#";
            }
        }
        cout << endl;
    }
    cout << endl << "SCORE: " << score << endl;
}

void controller() {
    if (_kbhit()) {
        char key = _getch();
        if (key == 'a') {
            --currentX;
            if (!isCanMove()) ++currentX;
        }
        if (key == 'd') {
            ++currentX;
            if (!isCanMove()) --currentX;
        }
        if (key == 's') {
            ++currentY;
            if (!isCanMove()) {
                --currentY;
                placeShape();
                clearLines();
                currentX = SCREEN_SIZE_X / 2 - 2;
                currentY = 0;
                currentRotation = 0;
                createShape();
            }
        }
        if (key == 'w') {
            rotateShape();
            if (!isCanMove()) {
                rotateShape();
                rotateShape();
                rotateShape();
            }
        }
    }
}

void createShape() {
    int index = rand() % 7;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            currentShape[i][j] = shapes[index][i][j];
        }
    }
}

void isGameOver() {
    if (field[0][SCREEN_SIZE_X / 2] == 1){
    	system("cls");
    	cout << "GAME OVER!" << endl;
    	cout << "YOUR SCORE: " << score << endl;
    	system("pause");
	}
}

int main() {
    srand(time(0));
    createShape();
    while (true) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (currentShape[i][j]) {
                    int x = currentX + j;
                    int y = currentY + i;
                    if (y >= 0 && y < SCREEN_SIZE_Y && x >= 0 && x < SCREEN_SIZE_X) {
                    }
                }
            }
        }
        drawScreen();
        controller();
        ++currentY;
        isGameOver();
        if (!isCanMove()) {
            --currentY;
            placeShape();
            clearLines();
            currentX = SCREEN_SIZE_X / 2 - 2;
            currentY = 0;
            currentRotation = 0;
            createShape();
        }
        Sleep(100);
    }
    return 0;
}
