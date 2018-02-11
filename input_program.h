/*******************************************************************

  Fichero     input_program.h

  Resumen     MÃ³dulo para la entrada por teclado por parte del usuario

  DescripciÃ³n MÃ³dulo para la entrada por teclado por parte del usuario. Ofrece
              funciones para leer un nÃºmero y una cadena por teclado. La cadena
              usada es una variable de mÃ³dulo. DespuÃ©s de usar el mÃ³dulo se 
              deberÃ¡ limpiar la memoria usada llamando a la funciÃ³n 
              correspondiente.

  Autor       Iria EstÃ©vez Ayres

  Copyright   [Copyright (c) 2016 Universidad Carlos III de Madrid

  Se concede, sin necesidad de acuerdo por escrito y sin ningÃºn tipo de derechos
  de autor, permiso para utilizar, copiar, modificar y distribuir este programa
  y su documentaciÃ³n para cualquier propÃ³sito siempre y cuando esta advertencia
  y los siguientes dos pÃ¡rrafos aparezcan en las copias.

  EN NINGÃšN CASO SE RECONOCERÃ A LA UNIVERSIDAD CARLOS III DE MADRID RESPONSABLE
  DIRECTA, INDIRECTA, ESPECIAL, O SUBSIDIARIA DE LOS POSIBLES DAÃ‘OS Y PERJUICIOS
  QUE PUEDAN DERIVARSE DEL USO DE ESTE PROGRAMA Y DE SU DOCUMENTACIÃ“N, INCLUSO
  EN EL CASO DE QUE LA UNIVERSIDAD CARLOS III DE MADRID HAYA SIDO ADVERTIDA DE
  TALES DAÃ‘OS Y PERJUICIOS.

  LA UNIVERSIDAD CARLOS III DE MADRID ESPECÃFICAMENTE SE DESENTIENDE DE TODO
  TIPO DE GARANTÃAS INCLUYENDO, PERO NO LIMITANDOLAS A, LAS GARANTIAS IMPLÃCITAS
  DE LA COMERCIALIZACIÃ“N Y ADECUACIÃ“N PARA CUALQUIER PROPÃ“SITO EN PARTICULAR. EL
  PROGRAMA SE PROVEE TAL CUAL Y LA UNIVERSIDAD CARLOS III DE MADRID NO TIENE
  OBLIGACIÃ“N ALGUNA DE OFRECER MANTENIMIENTO, SOPORTE, ACTUALIZACIONES, MEJORAS
  O MODIFICACIONES.]

******************************************************************************/

#ifndef INPUT_PROGRAM_H
#define INPUT_PROGRAM_H

/*---------------------------------------------------------------------------*/
/* DeclaraciÃ³n de constantes                                                 */
/*---------------------------------------------------------------------------*/

#define SUCCESS_INPUT 0
#define ERR_NO_NUMBERS_INPUT -1
#define ERR_FURTHER_CHARS_INPUT -2
#define ERR_CTRLD_INPUT -3

/*---------------------------------------------------------------------------*/
/* DeclaraciÃ³n de variables                                                  */
/*---------------------------------------------------------------------------*/

/*
 * Esta variable y esta constante deberÃ­an ser internas al mÃ³dulo y no expuesta en el .h 


#define NUM_INPUT_ERROR_MSGS 4

static const char *error_map[NUM_INPUT_ERROR_MSGS +1] =
  {
    "Success",
    "No digits were found",
    "Further characters after number",
    "CTRL+D was pressed (EOF)",
    "Unknown error"
  };

*/

/*---------------------------------------------------------------------------*/
/* Prototipos de las funciones                                               */
/*---------------------------------------------------------------------------*/

/*****************************************************************************

  Resumen      Entrada de una cadena por parte del usuario

  DescripciÃ³n  Espera la entrada de una cadena por teclado por parte del 
               usuario. Devuelve la cadena introducida por el usuario, a menos
               que el usuario haya introducido CTRL+D (EOF) o CTRL +C 
               (seÃ±al SIGINT)

  ParÃ¡metros   int *error: direcciÃ³n de una variable de tipo int donde devuelve
                           el error (si se produce). La cadena asociada al 
                           error se obtiene usando la funciÃ³n 
                           get_error_msg_input
               
  Efec. Colat. Se crea una cadena en el mÃ³dulo que deberÃ¡ ser liberada llamando
               a la funciÃ³n clean_module_input_program

  Ver tambiÃ©n  get_error_msg_input, clean_module_input_program

******************************************************************************/
char *get_string(int *error);

/*****************************************************************************

  Resumen      Entrada de un nÃºmero entero en la base seleccionada 
               por parte del usuario

  DescripciÃ³n  Espera la entrada de un nÃºmero entero por teclado por parte del 
               usuario en la base indicada. 
               Devuelve el nÃºmero introducida por el usuario, a menos
               que el usuario haya introducido CTRL+D (EOF condition).

  ParÃ¡metros   int base: base en la que se quiere el nÃºmero 
                         entero (e.g. 2, 10, 16)
               int *error: direcciÃ³n de una variable de tipo int donde devuelve
                           el error (si se produce). La cadena asociada al 
                           error se obtiene usando la funciÃ³n 
                           get_error_msg_input

******************************************************************************/
long get_number(int base, int *error);

/*****************************************************************************

  Resumen      Dado un error de este mÃ³dulo, devuelve la cadena asociada.

  DescripciÃ³n  Dado un error de este mÃ³dulo, devuelve la cadena asociada. 
               Se usan errores negativos y positivos en este mÃ³dulo (esto
               se podrÃ­a solucionar de otras maneras mÃ¡s elegantes). Los 
               negativos son los definidos en la variable error_map (se devuelve
               la cadena en la posiciÃ³n -error y los 
               positivos los que usan errno (y esta funciÃ³n devolverÃ­a
               directamente strerror(error). La funciÃ³n debe controlar cuando 
               error es negativo, que sea menor que el nÃºmero de 
               errores definidos en el mÃ³dulo.
  ParÃ¡metros   int error: error del que se quiere obtener la cadena de 
               error asociada.
  Ver tambiÃ©n  get_string, get_number

******************************************************************************/
const char *get_error_msg_input(int error);

/*****************************************************************************

  Resumen      Limpia el mÃ³dulo

  DescripciÃ³n  Libera la cadena interna al mÃ³dulo (variable global en el fichero
               input_program.c) al finalizar de usarlo. Esta funciÃ³n deberÃ¡
               ser usada por todas aquellas funciones que pretendan salir 
               totalmente del programa (como aquÃ©llas asociadas al manejo 
               de seÃ±ales)
  Ver tambiÃ©n  get_string

******************************************************************************/
void clean_module_input_program();

/* 
   Os copio tambiÃ©n los prototipos de las funciones internas al mÃ³dulo usadas
   por las otras funciones.
   Al ser internas NO deben ser declaradas en el .h
   EstÃ¡n en este comentario con fin Ãºnicamente orientativo (no tenÃ©is que
   implementar las mismas funciones internas).
   
   void free_cadena();
*/


#endif
