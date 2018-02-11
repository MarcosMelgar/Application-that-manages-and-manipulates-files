#include "collection.h"
#include "directorio.h"
#include "input_program.h"
#include "item.h"
#include "menu.h"
#include "senhal.h"
#include "util_files.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char const *argv[]) {


  inicialize_signal_handlers();
  my_collection = initialize_collection();

  print_menu();
  int errnum = 0;
  int error = 0;
  const char *string;
  
  comandos_t comando;

  comando = ask_command();

  while (comando.comando != EXIT) {
    //Help selected
    if(comando.comando == HELP){
      print_menu();
    }
    if(comando.comando == LOAD_DIR){
     my_collection = add_all_directory(my_collection, comando.opcional.arg_opt_char, &error);
     string = get_error_msg_collection(error);
     if (strcmp(string, "Success") != 0)
     {
      printf("Error: %s\n",string); 
     }
    }
    if(comando.comando == ADD_FILE){
      my_collection = add_file(my_collection,".", comando.opcional.arg_opt_char, &error);
      string = get_error_msg_collection(error);
      if (strcmp(string, "Success") != 0)
     {
      printf("Error: %s\n",string); 
     }
    }
    if (comando.comando == DEL_FILE){
     my_collection = delete_item_id(my_collection, comando.opcional.arg_opt_long, &errnum); 
     string = get_error_msg_collection(errnum);
      if (strcmp(string, "Success") != 0)
     {
      printf("Error: %s\n",string); 
     }
      
    }
    if (comando.comando == SORT){

      switch(comando.opcional.arg_opt_sort_t){

        case SORT_ID :

          my_collection = sort_collection( my_collection , compare_id);
          break;

        case SORT_NAME :

          my_collection = sort_collection(my_collection, compare_filename);
          break;

        case SORT_LAST_MODIFIED:

          my_collection = sort_collection(my_collection, compare_last_modified);
          break;

        case SORT_SIZE:

          my_collection = sort_collection(my_collection, compare_size);
          break;

        case SORT_INODE:

          my_collection = sort_collection(my_collection, compare_inode);
          break;

        default:
          printf("No sort criteria\n");
      }
    }
    if (comando.comando == INFO_FILE){  
      print_item_id(my_collection, comando.opcional.arg_opt_long,&error);
      string = get_error_msg_collection(error);
      if (strcmp(string, "Success") != 0)
      {
      printf("Error: %s\n",string); 
      }
    }
    if (comando.comando == INFO_ALL){
      printf("Info all\n");
      print_collection(my_collection);
    }

    printf("Please, enter an option (help: 7) : ");

    comando = ask_command();

  }
  
  //clears memory and goes out.
  clear_comando(comando);
  clean_module_input_program();
  my_collection = delete_collection(my_collection);
  clean_module_collection();

  printf("Peace out!...\n");
  
  return 0;
}

