#pragma once
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<deque>
#include<ctime>
#include<stdexcept>

using namespace std;

struct Snake {
	char image;
	short x, y;
};
class snakeGame {
public:
	snakeGame();
	void printMap();

	void gotoxy(short, short);

	void HideCursor();
	
	void initSnake();
	
	int WrongLocation();
	
	void createFood();
	void printSnake();
	
	inline void clearSnake(Snake& tail) {
		gotoxy(tail.x, tail.y); cout << ' '; 
	}
	void judgeCrash();
	void foodEaten();
	
	void userInput();
private:
	
	enum MapSize { height = 40, width = 120 }; 
	HANDLE hOut; COORD pos;
	char dir; 
	bool beg, eatFood = false;
	double speed = 200;
	deque<Snake> snake;
	int food_x, food_y;
	int score = 0;
};