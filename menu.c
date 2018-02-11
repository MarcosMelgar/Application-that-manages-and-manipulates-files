#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "collection.h"
#include "directorio.h"
#include "input_program.h"
#include "item.h"
#include "menu.h"
#include "senhal.h"
#include "util_files.h"

int error;
const char *string;

void print_menu(){
	printf("Management of a collection of files\nSelect one of these different options:\n1. load a directory\n2. add a file to the collection\n3. delete a file from the collection\n4. sort\n5. info about a file\n6. infoall\n7. help\n0. exit\n \nIf you enter CTRL+D in this menu, the program will exit in a controlled way.\nIf you enter CTRL+D in a submenu, the program will return to this menu.\n \nIf you enter CTRL+C (SIGINT) at any moment, the program will exit in a controlled way\nIf you enter CTRL+Z  (SIGTSTP) the collection will be sorted by inode number\n \nIf you send SIGUSR1 to the program, the collection will be sorted by filename\n \nPlease, enter an option (help: 7) : ");
}

comandos_t ask_command(){

	comandos_t comando;

	
	float terminal_output = get_number(10, &error);
	string = get_error_msg_input(error);

	while(strcmp(string, "Success") != 0)
	{
		if (strcmp(string, "CTRL+D was pressed (EOF)")== 0)
		{
			clean_module_input_program();
			clean_module_collection();
			exit(1);
		}
		printf("Error: %s\nPlease, enter a valid option\n",string);
		printf("Please, enter an option (help: 7) : ");
		terminal_output = get_number(10, &error);
		string = get_error_msg_input(error);
		
	}
	while(terminal_output > 7 || terminal_output < 0){

		if(strcmp(string, "Success") != 0)
			printf("Error: %s\nPlease, enter a valid option\n",string);
		else
			printf("Unknown option\n");
		
		printf("Please, enter an option (help: 7) : ");
		terminal_output = get_number(10, &error);
		string = get_error_msg_input(error);
	}

	if (terminal_output == 0)
	{
		comando.comando = EXIT;
	}
	if(terminal_output == 1)
	{
		comando.comando = LOAD_DIR;
		printf("Please, enter a directory name to load: \n");
      	comando.opcional.arg_opt_char =get_string(&error);
      	//comando.opcional.arg_opt_char[strlen(comando.opcional.arg_opt_char)-1]= '\0';
      	string = get_error_msg_input(error);
      	if(strcmp(string, "Success") != 0){
      		printf("Error: %s\nPlease, enter a valid option\n",string);
			printf("Please, enter an option (help: 7) : ");
			comando = ask_command();
      	}
	}
	if(terminal_output == 2)
	{
		comando.comando = ADD_FILE;
		printf("Please, enter a file name to add to the collection: \n");
		comando.opcional.arg_opt_char = get_string(&error);
		//comando.opcional.arg_opt_char[strlen(comando.opcional.arg_opt_char)-1]= '\0';
      	string = get_error_msg_input(error);
      	if(strcmp(string, "Success") != 0){
      		printf("Error: %s\nPlease, enter a valid option\n",string);
			printf("Please, enter an option (help: 7) : ");
			comando = ask_command();
      	}
	}
	if (terminal_output == 3)
	{
		comando.comando = DEL_FILE;
		printf("Please, enter a file identifier to delete from the collection: \n");
		comando.opcional.arg_opt_long = get_number(10,&error);
      	string = get_error_msg_input(error);
      	if(strcmp(string, "Success") != 0){
      		printf("Error: %s\nPlease, enter a valid option\n",string);
			printf("Please, enter an option (help: 7) : ");
			comando = ask_command();
		}
	}
	if (terminal_output == 4)
	{
		comando.comando = SORT;
		printf("Please introduce the type of sorting (0: by id; 1: by filename; 2: by modification time; 3: by size; 4: by inode number): \n");
		comando.opcional.arg_opt_sort_t = get_number(10, &error);
		string = get_error_msg_input(error);
		if(strcmp(string, "Success") != 0){
      		printf("Error: %s\nPlease, enter a valid option\n",string);
			printf("Please, enter an option (help: 7) : ");
			comando = ask_command();
      	}
      	if(comando.opcional.arg_opt_sort_t >4 || comando.opcional.arg_opt_sort_t < 0){
      		printf("Sort criterium not recognized\n");
      		printf("Please, enter an option (help: 7) : ");
      		comando = ask_command();
      	}

	}
	if (terminal_output == 5)
	{
		comando.comando = INFO_FILE;
		printf("Please, enter a file identifier to show its info: \n");
		comando.opcional.arg_opt_long =get_number(10,&error);
      	string = get_error_msg_input(error);
      	if(strcmp(string, "Success") != 0){
      		printf("Error: %s\nPlease, enter a valid option\n",string);
			printf("Please, enter an option (help: 7) : ");
			comando = ask_command();
      	}
	}
	if (terminal_output == 6)
	{
		comando.comando = INFO_ALL;
	}
	if (terminal_output == 7)
	{
		comando.comando = HELP;
	}

	return comando;
}

//comandos_t ask_option(){}


void clear_comando(comandos_t comando){
	if( (comando.comando == ADD_FILE || comando.comando == LOAD_DIR) && (strcmp(string, "Success") == 0))
		free(comando.opcional.arg_opt_char);
	}


  

