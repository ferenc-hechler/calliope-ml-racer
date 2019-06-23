#include <MicroBit.h>

#include "NN.h"
#include "Data.h"
#include "Vect.h"
#include "Utils.h"

extern MicroBit uBit;

bool isTrainIndex(int n) {
	return (n%5 != 0);
}

void train(NN *nn, Data *data) {
	float learning_rate = 0.001;
	for (int i=0; i<data->getCount(); i++) {
		if (isTrainIndex(i)) {
			Vect *x = data->getInput(i);
			Vect *y = data->getOutput(i);
			Vect *y_hat = nn->forwardPropagate(x);
			Vect *e = nn->backwardPropagate(y, y_hat, learning_rate);
			delete x;
			delete y;
			delete y_hat;
			delete e;
		}
	}
}

float test(NN *nn, Data *data) {
	float sum_err = 0;
	int cnt = 0;
	for (int i=0; i<data->getCount(); i++) {
		if (!isTrainIndex(i)) {
			cnt += 1;
			Vect *x = data->getInput(i);
			Vect *y = data->getOutput(i);
			Vect *y_hat = nn->forwardPropagate(x);
			y_hat->sub(y);
			y_hat->sqr();
			sum_err += y_hat->sum();
			delete x;
			delete y;
			delete y_hat;
		}
	}
	return sum_err/cnt;
}

void testIris() {
	log("Iris");

	Data *data = new Data();
	NN *nn = new NN(data->getNumInput());
	nn->addLayer(10);
	nn->addLayer(6);
	nn->addLayer(data->getNumOutput());
	logInt(nn->getNumLayers());

	float err;
	for (int i=0; i<=100; i++) {
		train(nn, data);
		err = test(nn, data);
		if (i%10 == 9) {
			uBit.rgb.setColour(255, 0, 0, 255);
		}
		else if (i%10 == 0) {
			uBit.rgb.setColour(255, 255, 255, 255);
		    uBit.soundmotor.soundOn(261.626);
		    uBit.sleep(100);
		    uBit.soundmotor.soundOff();
		    uBit.rgb.off();
			logInt(i);
			logFloat(err);
		}
		else if (i%2 == 0) {
		    uBit.rgb.setColour(127, 127, 0, 127);
		}
		else {
		    uBit.rgb.off();
		}
	}

    uBit.rgb.off();
    while ( uBit.buttonA.isPressed() == false ) {
    	log("erg");
    	logFloat(err);
    }
	log("end");
	delete nn;
	delete data;
}

void testNN() {
	testIris();
}





//#include <MicroBit.h>
//
//#include "NN.h"
//#include "Data.h"
//#include "Vect.h"
//#include "Utils.h"
//
//
//bool isTrainIndex(int n) {
//	return (n%5 != 0);
//}
//
//void train(NN *nn, Data *data) {
//	float learning_rate = 0.0001;
//	for (int i=0; i<data->getCount(); i++) {
//		if (isTrainIndex(i)) {
//			Vect *x = data->getInput(i);
//			Vect *y = data->getOutput(i);
//			Vect *y_hat = nn->forwardPropagate(x);
//			Vect *e = nn->backwardPropagate(y, y_hat, learning_rate);
//			delete x;
//			delete y;
//			delete y_hat;
//			delete e;
//		}
//	}
//}
//
//float test(NN *nn, Data *data) {
//	float sum_err = 0;
//	int cnt = 0;
//	for (int i=0; i<data->getCount(); i++) {
//		if (!isTrainIndex(i)) {
//			cnt += 1;
//			Vect *x = data->getInput(i);
//			Vect *y = data->getOutput(i);
//			Vect *y_hat = nn->forwardPropagate(x);
//			y_hat->sub(y);
//			y_hat->sqr();
//			sum_err += y_hat->sum();
//			delete x;
//			delete y;
//			delete y_hat;
//		}
//	}
//	return sum_err/cnt;
//}
//
//void testIris() {
//	log("Iris");
//
//	Data *data = new Data();
//
//	NN *nn = new NN(data->getNumInput());
//	nn->addLayer(20);
//	nn->addLayer(20);
//	nn->addLayer(data->getNumOutput());
//
//	for (int i=0; i<1; i++) {
//		train(nn, data);
//		float err = test(nn, data);
//		if (i%50 == 0) {
//			logInt(i);
//			logFloat(err);
//		}
//	}
//}
//
//void testNN() {
//	testIris();
//}
