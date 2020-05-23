#ifndef TASKPARAMS_H
#define TASKPARAMS_H
#include "TaskGenerator.h"
void vTaskCode( void * pvParameters );
struct TaskParams
{
    int tA;
    int tC;
    int tP;
		
		int priority;
	
	    void (*vTaskCode)( void * pvParameters );

};


#endif // !TASKPARAMS_H

