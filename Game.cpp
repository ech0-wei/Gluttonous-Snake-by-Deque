#include "Game.h"

using namespace std;


void snakeGame::gotoxy(short x, short y) {
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	pos = { x, y };
	SetConsoleCursorPosition(hOut, pos);
}
void snakeGame::HideCursor()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(handle, &CursorInfo);
}

void snakeGame::initSnake() {
	snake.push_front({ '@', width / 2, height / 2 });
	for (int i = 0; i < 2; ++i)
		snake.push_back({ '+', width / 2,static_cast<short>(height / 2 + i + 1) });
}

int snakeGame::WrongLocation() {
	for (Snake body : snake)
		if (body.x == food_x && body.y == food_y) return 0;
	return 1;
}
void snakeGame:: createFood() {
	do {
		food_x = rand() % (width - 4) + 2;
		food_y = rand() % (height - 2) + 1;
	} while (!WrongLocation());
	gotoxy(food_x, food_y); cout << '*' << endl; 
}

void snakeGame::foodEaten() {
	createFood();
	eatFood = true;
	speed *= .8;
	++score;
}

void snakeGame::judgeCrash() {
	int flag = 0;
	if (snake.size() >= 5) {
		deque<Snake>::iterator iter = snake.begin() + 1;
		int x = (iter - 1)->x, y = (iter - 1)->y;
		for (; iter != snake.end(); ++iter) {
			if (iter->x == x && iter->y == y) flag = 1;
		}
	}
	if (flag || snake.front().x == 1 || snake.front().x == width - 2 || snake.front().y == 0 || snake.front().y == height - 1)
	{
		gotoxy(width / 2 - 10, height / 2);
		cout << "Game Over£¬ Your score is : " << score << "(Enter to continue)" << endl;
		while (1) {
			dir = _getch();
			if (dir == '\r') break;
		}
		runtime_error quit("Game over quit!"); throw quit;
	}
}

void snakeGame::printSnake() {
	deque<Snake>::const_iterator iter = snake.begin();
	for (; iter <= snake.begin() + 1 && iter < snake.end(); ++iter) {
		gotoxy(iter->x, iter->y); cout << iter->image;
	}
}

void snakeGame::printMap() {
	int i;
	for (i = 0; i != width; i += 2) cout << "¡ö"; 
	gotoxy(0, 1);
	for (i = 1; i != height; ++i) cout << "¡ö" << endl;
	for (i = 1; i != height; ++i) {
		gotoxy(width - 2, i); cout << "¡ö";
	}
	gotoxy(0, height - 1);
	for (i = 0; i != width; i += 2) cout << "¡ö";
	cout << "Instruction£º1.Press Arrow to start 2.*is food 3.Space for pause\n        4.WSAD control direction    5.V speed up, B slow down ";
}
void snakeGame::userInput() {
	char ch;
	switch (ch = _getch()) {
	case 'w':if (dir != 's') dir = ch; break;
	case 'a':if (dir != 'd') dir = ch; break;
	case 's':if (dir != 'w') dir = ch; break;
	case 'd':if (dir != 'a') dir = ch; break;
	case 'v':speed *= 0.8; break; case 'b':speed *= 1.5; break;
	case ' ':gotoxy(width / 2, height); cout << "game stop, press any to continue"; _getch();
		gotoxy(width / 2, height); cout << "                     "; break;
	default:break;
	}
}

snakeGame::snakeGame() {
	HideCursor(); 
	srand(static_cast<unsigned int>(time(NULL)));
	beg = true;
	Snake tmp1, tmp2;
	while (1) {
		if (beg) { 
			printMap();
			dir = _getch();
			initSnake();
			createFood();
			beg = eatFood = false;
		}
		tmp2 = snake.back();
		tmp1 = snake.front();
		snake.pop_back();
		if (eatFood) { 
			tmp2.image = '+';
			snake.push_back(tmp2);
			eatFood = false;
		}
		else clearSnake(tmp2);
		
		if (dir == 's') ++tmp1.y;
		else if (dir == 'a') --tmp1.x;
		else if (dir == 'd') ++tmp1.x;
		else 				 --tmp1.y;
		try {
			judgeCrash();
		}
		catch (runtime_error& quitSignal) {
			throw quitSignal;
		}
		snake.front().image = '+';
		snake.push_front(tmp1);
		printSnake();
		Sleep(speed + 30);
		if (tmp1.x == food_x && tmp1.y == food_y)
			foodEaten();
		
		if (_kbhit()) userInput();
	}

}