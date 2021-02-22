#ifndef KI_H
#define KI_H

#define KI_MOVE_A 0
#define KI_MOVE_B 1
#define KI_MOVE_NONE 2

class NN;
class Race;

class KI
{
	NN* 	brain;
	int 	next;

public:
	KI(NN* theBrain);

	int doKiMove(int ms, Race* race);

	~KI();
};

#endif // KI_H
