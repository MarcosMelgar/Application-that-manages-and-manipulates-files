#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "collection.h"
#include "directorio.h"
#include "input_program.h"
#include "item.h"
#include "menu.h"
#include "senhal.h"
#include "util_files.h"


void signal_handlers(int senhal){

	//CTRL+Z
	if(senhal == SIGTSTP)
	{
		my_collection = sort_collection(my_collection, compare_inode);
	}
	//CTRL+C exits
	if(senhal == SIGINT)
	{
		clean_module_input_program();
		clean_module_collection();
		exit(1);
	}

	//SIGUSR1 received from another terminal
	if (senhal == SIGUSR1)
	{
		my_collection = sort_collection(my_collection, compare_filename);
	}
}


void inicialize_signal_handlers(){
	signal(SIGINT,  signal_handlers);
	signal(SIGTSTP, signal_handlers);
	signal(SIGUSR1, signal_handlers);
	
}
