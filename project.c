#include "tm4c123gh6pm.h"
#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "stdlib.h"
//#include "string.h"

#include "config.h"
#include "stdio.h"
#include "generator/TaskParam.h"
#include "generator/TaskGenerator.h"
#include "EventRecorder.h"              // Keil.ARM Compiler::Compiler:Event Recorder

#define MAX(a,b) (a>b ? a:b)
typedef int bool;
#define true 1
#define false 0
	
#define MAX_UCPU 0.7
const int first_priority = 1;

extern int n; //Number of tasks
//uint16_t* priorities;
uint16_t *pointers_to_tasks;

TaskHandle_t *xHandle;

uint32_t SystemCoreClock;

void vApplicationIdleHook()
{
	
}
bool scheduality_Test(struct TaskParams* params)
{
	double ucpu = 0;
	
	for(int i=0; i<n; i++) 
		ucpu += (float)params[i].tC/params[i].tP;
	
	return ucpu < MAX_UCPU ? true:false;
}

void swap(struct TaskParams* task1,struct TaskParams* task2){
	struct TaskParams temp;
	temp.tA = (*task1).tA;
	temp.tC = (*task1).tC;
	temp.tP = (*task1).tP;
	
	(*task1).tA = (*task2).tA;
	(*task1).tC = (*task2).tC;
	(*task1).tP = (*task2).tP;
	
	
	(*task2).tA = temp.tA;
	(*task2).tC = temp.tC;
	(*task2).tP = temp.tP;
}
void update_priorities(struct TaskParams* params)
{
	
			for (int i = 0; i < n-1; i++){      
		
				 for (int j = 0; j < n-i-1; j++){
						 if (params[j].tP < params[j+1].tP){ 
								swap(&params[j], &params[j+1]); 
						 }
					 }
			}
						 
			
			int tempPriority = first_priority;
			params[0].priority =first_priority;
					for (int i = 1; i < n; i++){
						if(params[i].tP!=params[i-1].tP){
							tempPriority++;
						}
						params[i].priority = tempPriority;
					}
		
}

void startTasks(struct TaskParams* params)
{
		BaseType_t xReturned;
		xHandle	= calloc(n,sizeof(TaskHandle_t));
		for (int i = 0; i < n-1; i++){      
			xTaskCreate(params[i].vTaskCode,       /* Function that implements the task. */
                    "gamed",          /* Text name for the task. */
                    STACK_SIZE,      /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    params[i].priority,/* Priority at which the task is created. */
                    &xHandle[i] );   
		}
}
int main() 
{
		EventRecorderInitialize(EventRecordAll, 1); //to redirect printf output to debug terminal
	
    struct TaskParams* params = GenerateTasksParameters(SAFE_MODE);
		
		//priorities = calloc(n,sizeof(uint16_t));
		pointers_to_tasks = calloc(n,sizeof(uint16_t));

		if(scheduality_Test(params)){
			printf("Tasks are schedulable\n");
				update_priorities(params);
				startTasks(params);
		}
		else{
			printf("Can't schedule tasks\n");
		}
    printf("ID)  A \t  P \t  C \t\tCPU%% \t\t       Rate \t\t   Priority\n");
		for(int i=0; i<n; i++) 
		{
        printf("T%d)%3d	%3d	%3d	", i, params[i].tA, params[i].tC, params[i].tP);
				printf("%3d /%3d = %4.3f", params[i].tC, params[i].tP,(float)params[i].tC/params[i].tP);
				printf("\t 1 /%3d = %4.3f", params[i].tP,(float)1.0f/params[i].tP);
				printf("\t\t\t%3d\n", params[i].priority);
		}
		
while (1);
}