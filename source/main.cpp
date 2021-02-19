/**
 * Calliope ML Racer
 *
 * Based ont the simple template for use with Calliope mini.
 * @copyright (c) Calliope gGmbH.
 * @author Matthias L. Jugel.
 * Licensed under the Apache License 2.0
 */

#include <MicroBit.h>

#include "TestNN.h"
#include "Utils.h"

#include "race/Race.h"

MicroBit uBit;

uint8_t world[25] = {
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0
};

uint8_t carPos = 2;

int background_cnt = 0;
int background_cnt2 = 0;

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

void runCar() {
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


/**
  * The timer callback, called from interrupt context once every SYSTEM_TICK_PERIOD_MS milliseconds.
  */
void background_tick()
{
	background_cnt++;
	if (background_cnt%20 == 0) {
		dbgLog(" A(");
		dbgLogInt(background_cnt);
		dbgLog(")a ");
	}
//        if (uBit.system_time() >= ...)
//        if (system_timer_current_time() >= f->context)
}


/**
  * The timer callback, called from interrupt context once every SYSTEM_TICK_PERIOD_MS milliseconds.
  */
void background_tick2()
{
	background_cnt2++;
	if (background_cnt2%11 == 0) {
		dbgLog(" B(");
		dbgLogInt(background_cnt2);
		dbgLog(")b ");
	}
}



// https://lancaster-university.github.io/microbit-docs/advanced/#initialising-the-fiber-scheduler
void initDebug() {
    uBit.serial.baud(115200);

    new MicroBitSystemTimerCallback(background_tick);
    new MicroBitSystemTimerCallback(background_tick2);

    dbgLog("\r\n\r\nCalliope mini template v1.0\r\n");
    dbgLog("Hello world!\r\n");
}

void runDebug() {
    dbgLog("BGCNT:");
    dbgLogInt(background_cnt);
    dbgLog("\r\n");
}


int main(void) {
    uBit.init();
    // log("start");

    race_main();

    log("finished");
    release_fiber();
    return 0;

//
//    initDebug();
//    runDebug();
//
//    for (int i=0; i<100; i++) {
//    	dbgLog(" I=[");
//    	dbgLogInt(i);
//    	dbgLog("] ");
//        background_tick();
//        background_tick2();
////    	uBit.sleep(0);
//    }
//
//    background_tick();
//    background_tick2();
//
//    return 0;
//
//    runCar();
//
//    runDebug();
//
////    testNN();
//
//    for (int i=0; i<100; i++) {
//    	dbgLog(" I=[");
//    	dbgLogInt(i);
//    	dbgLog("] ");
//    }
//
//    log("finished");
//    return 0;
}
