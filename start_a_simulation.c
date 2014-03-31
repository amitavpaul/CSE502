/*
An example code snippet which shows how we can communicate between System Under Test (system in Virtual Machine) and MARSS using PTLcalls API functions and Simconfig commands. 
If we run it with parameter 2 it sends the following commands to the MARSS:
-fast-fwd-user-insns 50000 -stopinsns 55000
-fast-fwd-user-insns 105000 -stopinsns 110000  
*/
#include "ptlcalls.h"
#include <stdio.h>
 
int main(int argc, char **argv) {
	char** commands;
	char fast_fwd[128];
	char stopinsns[128];
	
	long ins;	     
	int it, i;
	
	bzero(fast_fwd, 128);
	bzero(stopinsns, 128);
	
	if (argc != 2) {
		return -1;
	}
	it = atoi(argv[1]);
	commands = (char**) calloc (it*2,sizeof(char*));
	for (i=0; i < it*2; i++) {
		commands[i] = (char*) calloc (128,sizeof(char));
	}
	

	ins = 50000;
	for(i=1 ; i<=it ; i++){
		snprintf(commands[i*2-2], sizeof(fast_fwd), "-fast-fwd-user-insns %ld", ins);
		snprintf(commands[i*2-1], sizeof(stopinsns), "-stopinsns %ld", ins+5000);
		
		ptlcall_single_flush(commands[it*2-2]); 
		ptlcall_single_flush(commands[it*2-1]);
		
		ins += 55000;
	}
}
