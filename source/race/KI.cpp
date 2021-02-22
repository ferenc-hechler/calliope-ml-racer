#include <MicroBit.h>

#include "platform/Utils.h"
#include "neuralnets/NN.h"
#include "neuralnets/NNUtils.h"
#include "neuralnets/Vect.h"
#include "race/Car.h"
#include "race/Race.h"
#include "race/KI.h"

extern MicroBit uBit;


KI::KI(NN* theBrain)
{
	next = 200;
	brain = theBrain;
}


int KI::doKiMove(int ms, Race* race)
{
	next -= ms;
	if (next > 0) {
		return KI_MOVE_NONE;
	}
	next = 200;
	Vect x = createVect(6, 0.25f*race->getPlayer(), 0.2f*race->getCar(0), 0.2f*race->getCar(1), 0.2f*race->getCar(2), 0.2f*race->getCar(3), 0.2f*race->getCar(4));
	Vect *y_hat = brain->forwardPropagate(&x);
	int best = 0;
	float yMax = y_hat->get(best);
	if (yMax < y_hat->get(1)) {
		best = 1;
		yMax = y_hat->get(best);
	}
	if (yMax < y_hat->get(2)) {
		best = 2;
		yMax = y_hat->get(best);
	}
	delete y_hat;
	return best;
}

KI::~KI()
{
	// do not delete brain, it is owned outside.
	brain = 0;
}





