/*******************************************************************

  Fichero     directorio.h

  Resumen     MÃ³dulo para la lectura de contenidos de directorios.

  Autor       Iria EstÃ©vez Ayres

  Copyright   [Copyright (c) 2017 Universidad Carlos III de Madrid

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
#ifndef DIRECTORIO_H
#define DIRECTORIO_H
/* Se incluye la biblioteca dirent porque contiene la definiciÃ³n 
   de la estructura struct dirent */
#include <dirent.h>

/*****************************************************************************

  Resumen      Dado un nombre de directorio, lee los ficheros 
               que contiene (y devuelve en la variable info_files, que es un 
               array, su informaciÃ³n) 
               y devuelve el nÃºmero de ficheros existentes.
  DescripciÃ³n  Dado un nombre de directorio, lee los ficheros 
               que contiene (y devuelve en la variable info_files, que es un 
               array, su informaciÃ³n) 
               y devuelve el nÃºmero de ficheros existentes.
  ParÃ¡metros   char *path: nombre del directorio (se deberÃ¡ usar scandir)
               struct dirent ***info_files: direcciÃ³n de una variable de 
                           tipo struct dirent **
                           (array de struct dirent *) donde devuelve
                           los datos de todos los ficheros 
                           ese directorio.
                           Cuidado porque el campo dt_name de este array 
                           contiene los nombres absolutos de 
                           los ficheros por lo que se deberÃ¡ usar la funciÃ³n
                           realpath o una equivalente.
               int *error: direcciÃ³n de una variable de tipo int donde devuelve
                           el error (si se produce). En este caso, devuelve 
                           el valor de errno, por lo que el mensaje se 
                           deberÃ¡ imprimir usando strerror
               Devuelve el nÃºmero de ficheros leÃ­dos (la longitud del array
               all_files)         
  Efec. Colat. Se crean en memoria dinÃ¡mica tanto el array info_files como 
               cada uno de sus elementos,
               por lo que se deberÃ¡ llamar a free_info_files_array una 
               vez se procese el array.

******************************************************************************/
int info_all_files_dir(char *path, struct dirent ***info_files, int *error);

/*****************************************************************************

  Resumen      Dado un array de estructuras de tipo struct dirent y su 
               longitud, libera la memoria pedida.
  ParÃ¡metros   char **info_files: array pedido previamente por 
                                  info_all_filenames_dir
               int len: tamaÃ±o del array
               
******************************************************************************/
void free_info_files_array( struct dirent **info_files, int n);

/* 
  En este mÃ³dulo no he definido mÃ¡s funciones 
*/

#endif
