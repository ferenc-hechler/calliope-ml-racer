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

    dbgLog("\r\n");
	Race race;
	race.start();
	dbgLogF("\r\nScore %d\r\n\r\n", race.getScore());
	logF("Score %d", race.getScore());

	release_fiber();
    return 0;
}
