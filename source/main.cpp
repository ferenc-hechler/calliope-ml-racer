/**
 * Calliope ML Racer
 *
 * Based ont the simple template for use with Calliope mini.
 * @copyright (c) Calliope gGmbH.
 * @author Matthias L. Jugel.
 * Licensed under the Apache License 2.0
 */

#include <MicroBit.h>

#include "header.h"
#include "platform/Utils.h"
#include "race/Race.h"
#include "race/KI.h"
#include "neuralnets/NN.h"
#include "json/Parser.h"
#include "json/NNJsonParser.h"

MicroBit uBit;

#ifdef CREATE_JSON_INPUT_TEMPLATE
static const char * const JSON_INPUT = "                TeStTeXtTeStTeXt                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        ";
#else
static const char * const JSON_INPUT = "{\"params\":[{\"layers\":[6,7,7,3]},{\"act\":\"relu\"}],\"coefs\":[[[2.044017,-2.722454,2.000679,-1.514816,0.333606,-2.761747,-0.0],[0.028879,0.096323,-0.24589,0.015551,0.00977,0.001861,0.0],[-0.070218,-0.472358,0.379994,-0.024475,0.003899,-0.393389,0.0],[-0.74473,-0.013117,0.923773,0.1172,0.654482,0.33238,-0.0],[-0.03287,0.362568,0.806845,-0.332245,-0.198489,0.397769,0.0],[0.02064,0.011437,-0.209757,0.022583,0.077942,-0.015708,0.0]],[[-0.0,0.563227,-0.0,-0.196192,-2.71285,2.666878,1.751509],[0.0,-0.0,-0.0,1.679954,1.483361,-2.497833,-0.268884],[-0.0,0.118874,-0.0,-1.440332,-0.33425,0.058711,0.811402],[0.0,-5.311466,0.0,-0.468864,0.057601,-0.743952,1.867721],[-0.0,0.394793,-0.0,-0.382019,-0.52901,3.864352,1.189382],[0.0,-6.229019,0.0,2.250281,1.383958,2.699693,0.394597],[-0.0,-0.0,-0.0,-0.0,-0.0,0.0,-0.0]],[[-0.0,-0.0,0.0],[1.111976,2.797596,-2.238281],[0.0,-0.0,-0.0],[-6.529347,0.144358,3.030409],[3.251293,1.944163,-2.400912],[1.324108,-3.076313,1.005805],[-1.958187,-0.03444,2.36584]]],\"intercepts\":[[-0.449843,0.772355,-0.254264,1.384457,-0.668279,1.448058,-0.658712],[-0.591404,1.820663,-0.630498,0.797055,1.109102,0.036825,-1.220646],[-0.320211,1.158411,-1.175748]]}";
#endif

KI *getKI() {
	#ifdef SHOW_JSON_INPUT
    log(JSON_INPUT);
    log("\r\n");
	#endif

    NNJsonParser nnParser;
	Parser parser(&nnParser);

	parser.parse(JSON_INPUT);
	NN* brain = (NN*) nnParser.getResult();

	KI *result = 0;
	if (brain != 0) {
		#ifdef SHOW_NN_MATRIX
		brain->print();
		#endif
		result = new KI(brain);
	}
	return result;
}


int main(void) {
    uBit.init();

    log("\r\n");
    KI *ki = getKI();
	Race race(ki);
	race.start();
	logF("\r\nScore %d\r\n\r\n", race.getScore());
	showF("Score %d", race.getScore());

	release_fiber();
    return 0;
}


