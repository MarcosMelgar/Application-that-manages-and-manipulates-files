/*******************************************************************

  Fichero     item.h

  Resumen     MÃ³dulo para la gestiÃ³n, creaciÃ³n y manejo de los item de 
              la colecciÃ³n

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

#ifndef ITEM_H
#define ITEM_H

/*
  Esta biblioteca se incluye aquÃ­ y no en el .c 
  sÃ³lo porque es la que contiene la definiciÃ³n del tipo de 
  datos struct timespec
*/
#include <sys/stat.h>

/*---------------------------------------------------------------------------*/
/* DeclaraciÃ³n de estructuras                                                */
/*---------------------------------------------------------------------------*/


struct info{
  char *path;               /* path to the file */
  char *filename;           /* filename (relative) */
  char *abs_filename;       /* absolute name of the file */
  char *target_filename;     /* only if the file is a symbolic link */
  
  ino_t st_ino;             /* Inode Number */
  off_t     st_size;        /* total size, in bytes */
  nlink_t st_nlink;         /* number of hard links */
  struct timespec st_mtim;  /* time of last modification */
  mode_t st_mode;           /* protection, type of file*/

  uid_t owner;              /* numeric id of the owner */
  gid_t group;              /* numeric id of the group */
  
  /* name of the owner and of the group. They should be NULL if the names 
     are not found using the functions getpwuid and getgrgid */
  char *owner_name; 
  char *group_name;

};

struct item{
  int id; 
  struct info data;
};

/*****************************************************************************

  Resumen      Funciones que dadas las direcciones de dos items, los comparan 
               por id, por nombre, por fecha de Ãºltima modificaciÃ³n, por
               tamaÃ±o, por nÃºmero de inodo. 
               Estas funciones son usadas por la funciÃ³n de ordenaciÃ³n
  DescripciÃ³n  Funciones que dadas las direcciones de dos items, los comparan 
               por id, por nombre, por fecha de Ãºltima modificaciÃ³n y por
               tamaÃ±o. Estas funciones son usadas por la funciÃ³n de ordenaciÃ³n.
               Todas devuelven 0 si los Ã­tems son iguales, -1 si p < q y 1 si
               p > q
  ParÃ¡metros   const void *p DirecciÃ³n del primer item a comparar
               const void *q DirecciÃ³n del segundo item a comparar

******************************************************************************/

int compare_id(const void *p, const void *q);
int compare_filename(const void *p, const void *q);
int compare_last_modified(const void *p, const void *q);
int compare_size(const void *p, const void *q);
int compare_inode(const void *pa, const void *pb);

/*****************************************************************************

  Resumen      Dado un nombre de fichero, crea el item correspondiente.
  ParÃ¡metros   char *path: nombre del directorio.
               char *filename: nombre del fichero.
               char *abs_filename: nombre del fichero.
               int *error: direcciÃ³n de una variable de tipo int donde devuelve
                           el error (si se produce). En este caso, devuelve 
                           el valor de errno, por lo que el mensaje se 
                           deberÃ¡ imprimir usando strerror
               
  Efec. Colat. Se crean (en memoria dinÃ¡mica) las cadenas 
               path, filename, abs_filename, target_filename, owner_name 
               y group_name (estas tres Ãºltimas sÃ³lo si es necesario, tal
               y como indica la definiciÃ³n de la estructura). 
               Estas cadenas deberÃ¡n ser liberadas si se borra el elemento.

******************************************************************************/

struct item create_item(char *path, char *filename, char *abs_filename, struct stat info, int *error);

/*****************************************************************************
 Resumen      Dado un item, libera la memoria usada y deja sus 
              campos puntero a NULL
******************************************************************************/
void free_item(struct item *item);

/*****************************************************************************
 Resumen      Dado el campo st_mode del item, devuelve una cadena con los permisos.
******************************************************************************/

char *print_permissions(mode_t st_mode, char perms[], struct item foo);

/*****************************************************************************

  Resumen      Dado un item lo imprime por pantalla

******************************************************************************/

void print_item(struct item foo);

/* 
  En este mÃ³dulo he definido la siguiente funciÃ³n auxiliar:

  char letter_filetype(mode_t mode);
  Que devuelve un char dependiendo del tipo de fichero:
  Si es un fichero regular: '-' 
  Si es un directorio: 'd'
  Si es un fichero de bloque: 'b' 
  Si es un fichero de caracteres: 'c' 
  Si es un pipe: 'p' 
  Si es un enlace simbÃ³lico: 'l' 
  Si es un socket: 's' 
  Si es cualquier otra cosa: '?' 

 Usa las macros: S_ISREG(m), S_ISDIR(m), S_ISBLK(m), S_ISCHR(m), S_ISFIFO(m)
                 S_ISLNK(m), S_ISSOCK(m)
 Se puede encontrar informaciÃ³n sobre estas macros en la pÃ¡gina de manual
 de lstat
*/

#endif
