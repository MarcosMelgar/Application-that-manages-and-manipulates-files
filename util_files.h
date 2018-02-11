/*******************************************************************

  Fichero     util_files.h

  Resumen     MÃ³dulo para las funciones relativas a informaciÃ³n de ficheros
              del sistema operativo

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
#ifndef UTIL_FILES_H
#define UTIL_FILES_H
#include <sys/stat.h>

/*****************************************************************************

  Resumen      InformaciÃ³n acerca de un fichero
  DescripciÃ³n  Dado un directorio y un nombre de fichero, consulta su
               informaciÃ³n y su path absoluto.
  ParÃ¡metros   char *path: nombre del directorio
               char *filename: nombre del fichero  
               char **abs_filename: direcciÃ³n de una variable de tipo
                         char * (cadena), donde se guardarÃ¡ el path
                         absoluto del fichero. Para ello, se deberÃ¡ usar
                         realpath sobre el directorio y concatenar el
                         nombre de fichero
               struct stat *bufStat: direcciÃ³n de una variable de 
                           tipo struct stat donde devuelve
                           la informaciÃ³n relativa a ese fichero. 
                           Se deberÃ¡ usar la funciÃ³n lstat para consultar
                           la informaciÃ³n (ver la diferencia entre stat y
                           lstat en la pÃ¡gina de manual)
               int *error: direcciÃ³n de una variable de tipo int donde devuelve
                           el error (si se produce). En este caso, devuelve 
                           el valor de errno, por lo que el mensaje se 
                           deberÃ¡ imprimir usando strerror
               Devuelve si se ha producido un error. En este caso, devuelve 
               el valor de errno, por lo que el mensaje se deberÃ¡ imprimir 
               usando strerror.
  Efec. Colat. Si la llamada ha tenido Ã©xito, se crea en memoria dinÃ¡mica  
               abs_filename, por lo que se deberÃ¡ llamar a free cuando
               ya no se necesite.

******************************************************************************/

int info_file(char *path, char *filename, char **abs_filename,
	      struct stat *bufStat);

#endif
