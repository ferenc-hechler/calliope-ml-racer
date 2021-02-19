#ifndef CAR_H
#define CAR_H

#define PHASE_SLEEP  0
#define PHASE_MOVE   1

class Car
{
	int 	row;
	int     phase;
	int 	next;

public:
	Car();

	int getRow() const;
	bool move(int ms);


	~Car();
};

#endif // CAR_H
