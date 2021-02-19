#include <MicroBit.h>

#include "Utils.h"
#include "race/Race.h"

extern MicroBit uBit;


uint8_t disp[25] = {
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0
};

Race::Race()
{
	player = 2;
	tick = 0;
	score = 0;
	aPressed = false;
	bPressed = false;
	crash = 0;
}


int Race::getCar(int n) const
{
	return car[n].getRow();
}

int Race::getPlayer() const
{
	return player;
}

int Race::getTick() const
{
	return tick;
}

int Race::getScore() const
{
	return score;
}


void Race::print() const
{
	print("x");
}

void Race::print(const char *button) const
{
	dbgLogF("%d,%d,%d,%d,%d,%d,%s\r\n", player, getCar(0), getCar(1), getCar(2), getCar(3), getCar(4), button);
}

void Race::display() const
{
	for (int i=0; i<25; i++) {
		disp[i] = 0;
	}
	for (int i=0; i<5; i++) {
		int n = getCar(i);
		if ((n>0) && (n<=5)) {
			disp[i+n*5-5]=1;
		}
	}
	disp[20+player]=1;
	uBit.display.print(MicroBitImage(5, 5, disp));
}

void Race::move(int ms)
{
	for (int i=0; i<5; i++) {
		if (car[i].move(ms)) {
		    score++;
		}
	}
	handleButtons();
	tick++;
}

void Race::handleButtons() {
	if (uBit.buttonA.isPressed()) {
		if (!aPressed) {
			aPressed = true;
			onButtonAPressed();
		}
	}
	else {
		aPressed = false;
	}
	if (uBit.buttonB.isPressed()) {
		if (!bPressed) {
			bPressed = true;
			onButtonBPressed();
		}
	}
	else {
		bPressed = false;
	}
}

void Race::onButtonAPressed() {
	print("A");
	if (player > 0) {
		player--;
	}
}

void Race::onButtonBPressed() {
	print("B");
	if (player < 4) {
		player++;
	}
}

void Race::checkCrash() {
	if (getCar(player)==5) {
		crash = 1;
	}
}

void Race::showCrash() {
	for (int i=0; i<5; i++) {
		uBit.sleep(250);
		invertDisplay();
		uBit.sleep(500);
		invertDisplay();
	}
}

void Race::invertDisplay() {
	for (int i=0; i<25; i++) {
		disp[i] = 1 - disp[i];
	}
	uBit.display.print(MicroBitImage(5, 5, disp));
}

void Race::start()
{
	print();
	while (!crash) {
		move(10);
		display();
		if (tick%50 == 0) {
			print();
		}
		uBit.sleep(10);
		checkCrash();
	}
	showCrash();
}

Race::~Race()
{
}



void race_main() {
	Race race;
	race.start();
	dbgLogF("Score %d\r\n", race.getScore());
	logF("Score %d", race.getScore());
}





