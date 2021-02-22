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
#include "race/KI.h"
#include "neuralnets/NN.h"
#include "json/Parser.h"
#include "json/NNJsonParser.h"

MicroBit uBit;

const char *JSON_INPUT = "{\"params\":[{\"input_layer_size\":6},{\"output_layer_size\":3},{\"activation\":\"relu\",\"hidden_layer_sizes\":[5,5]}],\"coefs\":[[[-0.1774340,1.7180027,-2.2185390,-2.7157181,-1.8493312],[-0.2929120,-0.2159229,-0.1926039,0.4891134,0.5775759],[0.3595690,0.3887749,-0.0562094,-0.1737957,-0.5248434],[0.1492369,-0.4726848,0.5037789,-1.0239458,-0.8647448],[0.8280657,0.3250253,0.2636314,0.3337166,0.5085575],[-0.3032101,-0.0393003,-0.0539968,0.1071070,0.0712103]],[[-1.0918019,-0.3682515,-0.0070016,0.6161266,-4.7436538e-316],[1.1717495,1.3598602,-0.9327373,1.0735065,7.3903137e-316],[1.2006478,1.9328969,0.3707930,-3.3001615,-4.36019e-317],[-3.2961095,1.5889390,2.5617188,0.9860016,-1.0129486e-315],[2.6647761,-1.7936426,0.0199456,-0.8790681,4.6865165e-316]],[[1.9443124,-8.0195728,1.0388437],[3.7354118,-5.1001390,1.8261879],[-3.0452043,0.2562118,1.1356915],[-1.5016578,0.6879718,1.6212931],[-3.2343488e-315,3.8369143e-315,-3.0680620e-315]]],\"intercepts\":[[0.5143649,0.3070222,1.0359252,1.3399955,1.2130860],[-0.0479019,-1.8792909,1.7528952,-0.0097069,-0.6972091],[1.4335063,4.5834377,-3.2468793]]}";


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


