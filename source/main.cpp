/**
 * Calliope ML Racer
 *
 * Based ont the simple template for use with Calliope mini.
 * @copyright (c) Calliope gGmbH.
 * @author Matthias L. Jugel.
 * Licensed under the Apache License 2.0
 */

#include <MicroBit.h>

MicroBit uBit;

uint8_t world[25] = {
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0
};

uint8_t carPos = 2;

void setRandomObstacle() {
	if (uBit.random(100) < 50) {
		world[uBit.random(5)] = 1;
	}
}

void scrollDown() {
	for (int8_t z=19; z>=0; z--) {
		world[z+5] = world[z];
	}
	for (int8_t z=0; z<5; z++) {
		world[z] = 0;
	}
}

bool setCar() {
    bool result = world[20+carPos] == 1;
	world[20+carPos] = 1;
	return result;
}

void showWorld() {
    uBit.display.print(MicroBitImage(5, 5, world));
}

int main(void) {
    uBit.init();

	showWorld();

	uBit.soundmotor.soundOn(261.626);
    uBit.sleep(300);
    uBit.soundmotor.soundOff();

    bool crash = false;
    int runden = 0;
    while (!crash) {
    	runden += 1;

    	scrollDown();
    	setRandomObstacle();
		crash = setCar();
		showWorld();
        uBit.sleep(500);
        if ( uBit.buttonA.isPressed() == true ) {
        	if (carPos > 0) {
        		carPos -= 1;
        	}
        }
        if ( uBit.buttonB.isPressed() == true ) {
        	if (carPos < 4) {
        		carPos += 1;
        	}
        }
    }

	uBit.soundmotor.soundOn(130.813);
    uBit.sleep(300);
    uBit.soundmotor.soundOff();

	uBit.display.scroll("Runden:");
	uBit.display.scroll(ManagedString(runden));

}
