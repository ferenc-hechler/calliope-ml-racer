#ifndef DATA_H
#define DATA_H

class Vect;

class Data
{
	float *data;
	int count;
	int numInput;
	int numOutput;

public:

	Data();
	int getCount();
	int getNumInput();
	int getNumOutput();
	Vect* getInput(int n);
	Vect* getOutput(int n);
	~Data();
};

#endif
