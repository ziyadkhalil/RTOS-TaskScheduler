#include "config.h"
#include "stdio.h"
#include "TaskParam.h"
#include "TaskGenerator.h"

extern int n; //Number of tasks





int main() {
    struct TaskParams* params = GenerateTasksParameters(SAFE_MODE);
    for(int i=0; i<n; i++) {
        printf("Task %d: tA is %d, tC is %d and tP is %d\n", i, params[i].tA, params[i].tC, params[i].tP);
    }
    return 0;
}

