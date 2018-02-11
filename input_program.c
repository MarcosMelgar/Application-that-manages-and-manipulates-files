#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include "input_program.h"

#define NUM_INPUT_ERROR_MSGS 4



char *cadena = NULL;
size_t number_alloc=0;


void clean_module_input_program(){

	if(cadena != NULL ){
		free(cadena);
		cadena = NULL;
		number_alloc = 0;
	}

}

static const char *error_map[NUM_INPUT_ERROR_MSGS +1] = {"Success","No digits were found", 
"Further characters after number","CTRL+D was pressed (EOF)","Unknown error"};


const char *get_error_msg_input(int error){

  if(error < 0){

    if(-error >= NUM_INPUT_ERROR_MSGS){
      return error_map[4];
    }
    return error_map[-error];
  }

  return strerror(error);  
}

char *get_string(int *error){

  *error = 0;
  errno = 0;
  size_t n_read;
  n_read = getline(&cadena, &number_alloc, stdin); //stdin-> meter en la lÃ­nea de comandos.

  if(n_read == -1){ 

      if(errno != 0){
        *error = errno;
      return NULL;
      }

    *error = ERR_CTRLD_INPUT;
    clean_module_input_program();
    return NULL;    
  }


  if (strlen(cadena) > 1) {
    cadena[strlen(cadena)-1] = 0;
  }
  return cadena;

}


long get_number(int base, int *error){

  char *ptr = NULL;
  char *cadena;
  cadena = get_string(error);

  if(cadena == NULL){
    return -1;
  }

  long number = strtol(cadena, &ptr, base); //Convierte una cadena en un long.

  if(strcmp(ptr, cadena) == 0){
    *error = ERR_NO_NUMBERS_INPUT;
    return -1;
  }

  if(ptr == NULL){ //Se ha pulsado CTRL+D.
    *error = ERR_CTRLD_INPUT;
    return -1;
  }

  if(strcmp(ptr, "\0") != 0){ //Si no me devuelve 0 es que tiene algo mÃ¡s que nÃºmeros.
    *error = ERR_FURTHER_CHARS_INPUT;
    return -1;
  }

  *error = SUCCESS_INPUT;

  return number;
}












