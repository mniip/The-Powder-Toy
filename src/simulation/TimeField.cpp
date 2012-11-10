#include <cmath>
#include <algorithm>
#include "Config.h"
#include "TimeField.h"
#include "Simulation.h"

void TimeField::update_time(){
    float nt[YRES/CELL][XRES/CELL];
	std::fill(&nt[0][0], &nt[0][0]+((XRES/CELL)*(YRES/CELL)), 0.0f);
	for(int i=1;i<YRES/CELL-1;i++)
        for(int j=1;j<XRES/CELL-1;j++){
            float v=(field[i+1][j]+field[i-1][j]+field[i][j+1]+field[i][j-1]+field[i][j])/5;
            if(v>16)
                v=16;
            else if(v<-16)
                v=-16;
            nt[i][j]=v;
        }
    memcpy(field,nt,sizeof(field));
}
void TimeField::Clear(){
	std::fill(&field[0][0], &field[0][0]+((XRES/CELL)*(YRES/CELL)), 0.0f);
}
TimeField::TimeField(){
    Clear();
}
