 
#include <stdio.h>
#include "time.h"
#include "stdlib.h"

#include "config.h"
#include "stdio.h"
#include "generator/TaskParam.h"
#include "generator/TaskGenerator.h"

#include "ARMCM0.h"
#include "EventRecorder.h"              // Keil.ARM Compiler::Compiler:Event Recorder

int main() {
	EventRecorderInitialize(EventRecordAll, 1); //to redirect printf output to debug terminal

	printf("HIIIII");
	
return 0;
}