/*******************************************************************

  Fichero     collection.h

  Resumen     MÃ³dulo para la gestiÃ³n, creaciÃ³n y manejo de la colecciÃ³n

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


#ifndef COLLECTION_H
#define COLLECTION_H
/*Esta biblioteca es necesario incluirla aquÃ­ para definir los items de la
  colecciÃ³n*/
#include "item.h"

/*---------------------------------------------------------------------------*/
/* DeclaraciÃ³n de constantes                                                 */
/*---------------------------------------------------------------------------*/


#define INI_SIZE 20
#define SUCCESS_INPUT 0
#define ERR_NO_COLLECTION -1
#define ERR_NO_FREE_SPACE_COLLECTION -2
#define ERR_ELEMENT_ALREADY_COLL -3
#define MORE_FILES_THAN_SPACE -4
#define FILE_DOES_NOT_EXIST -5
#define ELEMENT_NOT_FOUND -6

#define NUM_COLLECTION_ERROR_MSGS 7

/*---------------------------------------------------------------------------*/
/* DeclaraciÃ³n de estructuras                                                */
/*---------------------------------------------------------------------------*/

struct collection{

  int total_capacity;
  int number_occupied;
  /*To be changed*/
  struct item *tabla;
};

/*---------------------------------------------------------------------------*/
/* DeclaraciÃ³n de variables                                                  */
/*---------------------------------------------------------------------------*/
/*
 * Esta variable es interna al mÃ³dulo y no expuesta en el .h 
   EStÃ¡ definida en el mÃ³dulo. Os la he copiado aquÃ­ con fines educativos
static const char *error_map_coll[NUM_COLLECTION_ERROR_MSGS] =
  {
    "Success",
    "No elements within the collection",
    "Total Capacity Reached",
    "Element already in the collection",
    "There were more files than space in the collection",
    "File does not exist",
    "Element not found"
  };

 */

/* 
   Esta variable estÃ¡ definida aquÃ­ sÃ³lo para poder ser usada por las
   funciones de manejo de seÃ±ales. No se debe usar para otro fin
   EstÃ¡ definida en el .c como variable global al mÃ³dulo.
*/
extern struct collection my_collection;

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
******************************************************************************/
const char *get_error_msg_collection(int error);

/*****************************************************************************

  Resumen      Inicializa la colecciÃ³n a tamaÃ±o inicial INI_SIZE y 
               number_occupied a 0
******************************************************************************/
struct collection initialize_collection();

/*****************************************************************************

  Resumen      Busca un item por nombre en la colecciÃ³n.
  DescripciÃ³n  Devuelve 0 si lo encuentra y lo contrario si no.
               int *error bÃ¡sicamente devuelve si my_collection estÃ¡ vacÃ­a o no.
******************************************************************************/



int buscar_item_nombre(struct collection my_collection, char *nombre,int *error);


/*****************************************************************************

  Resumen      Busca un item pÃ²r id en la colecciÃ³n y devuelve su posiciÃ³n.
  DescripciÃ³n  Devuelve su posiciÃ³n si lo encuentra y -1 si no.
******************************************************************************/


int buscar_item_id(struct collection my_collection, int id, int *error);

/*****************************************************************************

  Resumen      Libera toda la memoria reservada por este mÃ³dulo.
  DescripciÃ³n  Esta funciÃ³n deberÃ¡ ser llamada al finalizar el programa para
               liberar toda la memoria.
******************************************************************************/

void clean_module_collection();

/*****************************************************************************

  Resumen      Dado un nombre de fichero lo aÃ±ade, si es posible, a la 
               colecciÃ³n.

  DescripciÃ³n  Dado un nombre de fichero lo aÃ±ade, si es posible, a la 
               colecciÃ³n. Si el fichero no existe o si ya existe en la 
               colecciÃ³n no lo aÃ±ade. Esta funciÃ³n es la encargada de 
               aÃ±adir el identificador Ãºnico a cada nuevo item (los 
               identificadores no se reutilizan).
  ParÃ¡metros   struct collection my_collection: la colecciÃ³n a la que se 
                           va a aÃ±adir el nuevo fichero
               char *path: nombre del directorio donde estÃ¡ el fichero
               char *nombre: nombre del fichero a aÃ±adir               
               int *error: direcciÃ³n de una variable de tipo int donde devuelve
                           el error (si se produce). La cadena asociada al 
                           error se obtiene usando la funciÃ³n 
                           get_error_msg_collection

  Efec. Col.   Se guarda el nombre del fichero en memoria dinÃ¡mica, por lo que 
               se deberÃ¡ liberar llamando a clean_module_collection

******************************************************************************/
struct collection add_file(struct collection my_collection,
			   char *path, char *nombre, int *error);
/*****************************************************************************

  Resumen      AÃ±ade todos los ficheros a la colecciÃ³n

  DescripciÃ³n  Dado un nombre de directorio aÃ±ade todos los ficheros que 
               sea posible a la colecciÃ³n. Si el fichero no existe o si 
               ya existe en la colecciÃ³n no lo aÃ±ade.
               Para comprobar si ya existe comprueba su abs_filename.
  ParÃ¡metros   struct collection my_collection: la colecciÃ³n a la que se 
                           van a aÃ±adir todos los ficheros que sea posible
                           del directorio path 
               char *path: nombre del directorio donde estÃ¡n los ficheros a 
                           aÃ±adir.
               int *error: direcciÃ³n de una variable de tipo int donde devuelve
                           el error (si se produce). La cadena asociada al 
                           error se obtiene usando la funciÃ³n 
                           get_error_msg_collection

  Efec. Col.   Se guarda el nombre de los ficheros en memoria dinÃ¡mica, por 
               lo que se deberÃ¡ liberar llamando a clean_module_collection

******************************************************************************/

struct collection add_all_directory(struct collection my_collection,
				    char *path, int *error);

/*****************************************************************************
  Resumen      Dado un identificador Ãºnico en la colecciÃ³n lo borra, si es 
               posible, de la colecciÃ³n. 
  ParÃ¡metros   struct collection my_collection: la colecciÃ³n de la que se 
                       va a borrar el fichero
               int id: identificador Ãºnico del fichero a borrar.       
               int *error: direcciÃ³n de una variable de tipo int donde devuelve
                           el error (si se produce). La cadena asociada al 
                           error se obtiene usando la funciÃ³n 
                           get_error_msg_collection

******************************************************************************/
struct collection delete_item_id(struct collection my_collection,
				 int id, int *errnum);


/*****************************************************************************
  Resumen      Dada una colecciÃ³n, elimina todos sus elementos. La colecciÃ³n
               que se devuelve estÃ¡ en el mismo estado que una colecciÃ³n
               reciÃ©n inicializada.
  ParÃ¡metros   struct collection my_collection: la colecciÃ³n que se va a borrar.

******************************************************************************/
struct collection delete_collection(struct collection my_collection);

/*****************************************************************************
  Resumen      Dado un identificador Ãºnico en la colecciÃ³n lo borra, si es 
               posible, tanto de la colecciÃ³n como del sistema de ficheros.
  ParÃ¡metros   struct collection my_collection: la colecciÃ³n que se va a 
                           ordenar
               compare: funciÃ³n de comparaciÃ³n entre items de la tabla.
******************************************************************************/

struct collection sort_collection(struct collection my_collection,
				  int (*compare)(const void *, const void *));

/*****************************************************************************
  Resumen      Dado un identificador Ãºnico en la colecciÃ³n, imprime su 
               informaciÃ³n.
  ParÃ¡metros   struct collection my_collection: la colecciÃ³n 
               int id: identificador Ãºnico del fichero
               int *errnum:  direcciÃ³n de una variable de tipo int 
                           donde devuelve el error (si se produce). 
                           La cadena asociada al error se obtiene usando 
                           la funciÃ³n get_error_msg_collection
******************************************************************************/
void print_item_id(struct collection my_collection, int id, int *errnum);

/*****************************************************************************
  Resumen      Dada la colecciÃ³n, la imprime
  ParÃ¡metros   struct collection my_collection: la colecciÃ³n 
******************************************************************************/

void print_collection(struct collection my_collection);


/* 
   Os copio tambiÃ©n los prototipos de las funciones internas al mÃ³dulo usadas
   por las otras funciones.
   Al ser internas NO deben ser declaradas en el .h
   EstÃ¡n en este comentario con fin Ãºnicamente orientativo (no tenÃ©is que
   implementar las mismas funciones internas).
   
   void print_cabecera();
   int find_item(struct collection my_collection, int id, int *error);
   int find_item_name(struct collection my_collection, char *abs_name, int *error);
*/
#endif
