#include "TaskParam.h"
#include "TaskGenerator.h"
#include "../config.h"
#include "stdlib.h"	
#include <stdio.h>
#include "Hash.h"

int n;
/**
 * 
 * @param mode either SAFE_MODE or NO_GUARANTEE_MODE
 * @return a pointer to params
 */
struct TaskParams* GenerateTasksParameters(int mode) {


	//Every time you build edit this comment for the timestamp of the compiler changes
	//Edits = 4
	srand(hash(__TIME__)); // use compilation time as seed for random generator
	printf("Time is : %s \nSeed is ->%lu  \n",__TIME__,hash(__TIME__));	

	n = 2 + rand() % (N-1);   //Setting number of tasks
    struct TaskParams* params = (struct TaskParams*) calloc(n, sizeof(struct TaskParams)); //Allocating memory for the [TaskParams]
	
    for (int i=0; i<n; i++) {
        params[i].tA = rand() % (LATEST_ARRIVAL_TIME + 1);
        params[i].tC = (1 + rand() % (MAXIMUM_COMPUTATION_TIME/TST)) * TST;
        if (mode == SAFE_MODE)
            params[i].tP = 3*params[i].tC + rand() % (MAXIMUM_PERIOD_MULTIPLIER*params[i].tC - 3*params[i].tC + 1);
        else 
            params[i].tP = 3*params[i].tC + rand() % (10*params[i].tC - 3*params[i].tC +1);
    }
    return params;
}