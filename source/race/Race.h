#ifndef RACE_MAIN_H
#define RACE_MAIN_H

#include "race/Car.h"

class Race
{
	int 	score;
	int     crash;
	int 	tick;
	int     player;
	Car     car[5];
	bool    aPressed;
	bool    bPressed;

public:
	Race();

	void start();

	void move(int ms);
	void handleButtons();
	void onButtonAPressed();
	void onButtonBPressed();

	void checkCrash();
	void showCrash();
	void invertDisplay();

	int getCar(int n) const;
	int getPlayer() const;
	int getTick() const;
	int getScore() const;

	void display() const;
	void print() const;
	void print(const char *button) const;

	~Race();
};

void race_main();

#endif // RACE_MAIN_H
