/**
 * Calliope ML Racer
 *
 * Based ont the simple template for use with Calliope mini.
 * @copyright (c) Calliope gGmbH.
 * @author Matthias L. Jugel.
 * Licensed under the Apache License 2.0
 */

#include <MicroBit.h>

#include "platform/Utils.h"
#include "race/Race.h"

MicroBit uBit;



int main(void) {
    uBit.init();

    log("\r\n");
	Race race;
	race.start();
	logF("\r\nScore %d\r\n\r\n", race.getScore());
	showF("Score %d", race.getScore());

	release_fiber();
    return 0;
}
