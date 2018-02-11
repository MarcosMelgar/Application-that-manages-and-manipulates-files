/*******************************************************************

  Fichero     menu.h

  Resumen     MÃ³dulo para la gestiÃ³n de los menÃºs con el usuario

  DescripciÃ³n MÃ³dulo para la gestiÃ³n de los menÃºs con el usuario.

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
#ifndef MENU_H
#define MENU_H

/*---------------------------------------------------------------------------*/
/* DeclaraciÃ³n de tipos                                                      */
/*---------------------------------------------------------------------------*/

enum comandos_type{EXIT, LOAD_DIR, ADD_FILE, DEL_FILE, SORT, INFO_FILE,INFO_ALL, HELP};

enum sort_type{SORT_ID, SORT_NAME, SORT_LAST_MODIFIED,SORT_SIZE,SORT_INODE};

/*---------------------------------------------------------------------------*/
/* DeclaraciÃ³n de estructuras                                                */
/*---------------------------------------------------------------------------*/

union opcional_t{
  char *arg_opt_char;
  long arg_opt_long;
  enum sort_type arg_opt_sort_t;
};

struct comandos{
  enum comandos_type comando;
  union opcional_t opcional;
};

typedef struct comandos comandos_t;


/*****************************************************************************

  Resumen      Imprime el menÃº

******************************************************************************/
void print_menu();

/*****************************************************************************

  Resumen      Entrada de una opciÃ³n vÃ¡lida por parte del usuario

  DescripciÃ³n  Espera la entrada de una opciÃ³n vÃ¡lida por parte del usuario.
               Devuelve el comando introducido y su parÃ¡metro opcional si
               lo hubiere en una estructura de tipo comandos_t.

  Efec. Colat. Si el comando tiene como parÃ¡metro opcional una cadena y
               sÃ³lo en ese caso, se crea una cadena en el mÃ³dulo que
               deberÃ¡ ser liberada llamando a la funciÃ³n clear_comando nada
               mÃ¡s terminar de usar el parÃ¡metro devuelto.

  Ver tambiÃ©n  clear_comando

******************************************************************************/
comandos_t ask_command();

/*****************************************************************************

  Resumen      Libera la cadena de parÃ¡metros generada al usar ask_command

  Ver tambiÃ©n  ask_command

******************************************************************************/
void clear_comando(comandos_t comando);

/*
   Os copio tambiÃ©n los prototipos de las funciones internas al mÃ³dulo usadas
   por las otras funciones.
   Al ser internas NO deben ser declaradas en el .h

   comandos_t ask_char_opt(char *msg, enum comandos_type cte_comando, int *opt_desired);
   comandos_t ask_long_opt(char *msg, enum comandos_type cte_comando, int *opt_desired);

   IMPORTANTE: aunque yo he usado estas funciones internamente NO es obligatorio
   implementarlas, podÃ©is implementar otras. Lo importante es que ask_command funcione como debe

*/

#endif
