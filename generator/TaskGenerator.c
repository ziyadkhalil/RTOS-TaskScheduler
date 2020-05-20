#include "TaskParam.h"
#include "TaskGenerator.h"
#include "../config.h"
#include "time.h"
#include "stdlib.h"
int n;
/**
 * 
 * @param mode either SAFE_MODE or NO_GUARANTEE_MODE
 * @return a pointer to params
 */
struct TaskParams* GenerateTasksParameters(int mode) {
    srand(time(0)); // use current time as seed for random generator
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