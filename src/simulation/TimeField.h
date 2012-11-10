#ifndef TIMEFIELD_H
#define TIMEFIELD_H
#include "Config.h"

class Simulation;

class TimeField
{
public:
	float field[YRES/CELL][XRES/CELL];
	float nt[YRES/CELL][XRES/CELL];
	void update_time(void);
	void Clear();
	TimeField();
};

#endif
