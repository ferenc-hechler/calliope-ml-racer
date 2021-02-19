#include <MicroBit.h>

#include "platform/Utils.h"
#include "race/Car.h"

extern MicroBit uBit;


Car::Car()
{
	row = 1;
	phase = PHASE_SLEEP;
	next = 100;
}


int Car::getRow() const
{
	return row;
}


bool Car::move(int ms)
{
	next -= ms;
	if (next > 0) {
		return false;
	}
	switch (phase) {
	case PHASE_SLEEP:
		next = uBit.random(5001);
		phase = PHASE_MOVE;
		break;
	case PHASE_MOVE:
		if (row == 5) {
			row = 0;
			next = uBit.random(5001);
			return true;
		}
		row += 1;
		next = 500;
		break;
	}
	return false;
}

Car::~Car()
{
}





