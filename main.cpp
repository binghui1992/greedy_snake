#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

const int WIDTH = 20;
const int HEIGHT = 20;

enum Direction { UP, DOWN, LEFT, RIGHT };

struct Snake {
    vector<pair<int, int>> body;
    Direction dir;
};

void setup(Snake& snake, pair<int, int>& food) {
    snake.body = {{WIDTH / 2, HEIGHT / 2}};
    snake.dir = RIGHT;
    srand(time(0));
    food = {rand() % WIDTH, rand() % HEIGHT};
}

void draw(const Snake& snake, const pair<int, int>& food) {
    system("cls");
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                cout << "#";
            } else if (make_pair(j, i) == food) {
                cout << "F";
            } else {
                bool isSnake = false;
                for (const auto& part : snake.body) {
                    if (part == make_pair(j, i)) {
                        cout << "O";
                        isSnake = true;
                        break;
                    }
                }
                if (!isSnake) cout << " ";
            }
        }
        cout << endl;
    }
}

void input(Snake& snake) {
    if (_kbhit()) {
        char key = _getch();
        switch (key) {
            case 'w': if (snake.dir != DOWN) snake.dir = UP; break;
            case 's': if (snake.dir != UP) snake.dir = DOWN; break;
            case 'a': if (snake.dir != RIGHT) snake.dir = LEFT; break;
            case 'd': if (snake.dir != LEFT) snake.dir = RIGHT; break;
        }
    }
}

void logic(Snake& snake, pair<int, int>& food, bool& gameOver) {
    pair<int, int> head = snake.body[0];
    switch (snake.dir) {
        case UP: head.second--; break;
        case DOWN: head.second++; break;
        case LEFT: head.first--; break;
        case RIGHT: head.first++; break;
    }
    if (head.first < 1 || head.first >= WIDTH - 1 || head.second < 1 || head.second >= HEIGHT - 1) {
        gameOver = true;
        return;
    }
    for (size_t i = 1; i < snake.body.size(); ++i) {
        if (head == snake.body[i]) {
            gameOver = true;
            return;
        }
    }
    snake.body.insert(snake.body.begin(), head);
    if (head == food) {
        food = {rand() % (WIDTH - 2) + 1, rand() % (HEIGHT - 2) + 1};
    } else {
        snake.body.pop_back();
    }
}

int main() {
    Snake snake;
    pair<int, int> food;
    bool gameOver = false;
    setup(snake, food);
    while (!gameOver) {
        draw(snake, food);
        input(snake);
        logic(snake, food, gameOver);
        Sleep(100);
    }
    cout << "Game Over!" << endl;
    return 0;
}