#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include "collection.h"
#include "item.h"
#include "directorio.h"
#include "util_files.h"



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


 struct collection my_collection;

 struct collection initialize_collection(){
 	my_collection.number_occupied = 0;
 	my_collection.total_capacity = INI_SIZE;
    my_collection.tabla = (struct item *) malloc(sizeof(struct item)*INI_SIZE);
    if(my_collection.tabla == NULL){
        printf("An error happened while allocating memory\n");
        my_collection.total_capacity = 0;
    }
    return my_collection;
 }

 struct collection delete_collection(struct collection my_collection){

 	int i;
 	for ( i=0 ; i < my_collection.number_occupied; i++)
 	{
 		free_item(&my_collection.tabla[i]);
 	}

 	my_collection.number_occupied = 0;

    if(my_collection.total_capacity > INI_SIZE){
        my_collection.tabla = (struct item*) realloc(my_collection.tabla, sizeof(struct item)*INI_SIZE);
        return my_collection;
    }

 	return my_collection;

 }

 void clean_module_collection(){
 	free(my_collection.tabla);
 }

 const char *get_error_msg_collection(int error){
 	if(error >= 0)
 		return strerror(error);
 	else if( (error*-1) > NUM_COLLECTION_ERROR_MSGS ){
 		return error_map_coll[NUM_COLLECTION_ERROR_MSGS];
 	}
 	else{
 		return error_map_coll[error*(-1)];
 	}
 }

 struct collection add_file(struct collection my_collection, char *path, char *nombre, int *error){
 	
 	int position = my_collection.number_occupied;
 	struct stat info;
 	char *dirAbs = NULL;


    //manejo de errores
    if(my_collection.total_capacity == 0){
        *error = ERR_NO_COLLECTION;
        return my_collection;
    }
    if (access(nombre, F_OK) < 0) {
        *error = FILE_DOES_NOT_EXIST;
        return my_collection;
    }
    if (buscar_item_nombre(my_collection, nombre, error) == 0) {
        *error = ERR_ELEMENT_ALREADY_COLL;
        return my_collection;
    }
    if (my_collection.number_occupied == INI_SIZE){
        *error = ERR_NO_FREE_SPACE_COLLECTION;
        printf("No free space in the collection (resizing) \n");
        my_collection.tabla = (struct item*)realloc(my_collection.tabla, 2*my_collection.total_capacity*sizeof(struct item));
        if(my_collection.tabla == NULL){
            *error = errno;
            printf("Can not resize collection\n");
        }
        my_collection.total_capacity = my_collection.total_capacity*2;
    }
    
    
    *error = SUCCESS_INPUT;

 	info_file(path, nombre, &dirAbs, &info);
 	my_collection.tabla[position] = create_item(path, nombre, dirAbs, info, error);
    my_collection.tabla[position].id = position;
 	my_collection.number_occupied++;

    if(dirAbs != NULL){
        free(dirAbs);
    }

 	return my_collection;

 }

 struct collection add_all_directory(struct collection my_collection, char *path, int *error){

    struct dirent **allfiles; //array of struct dirent with info of all files
    int number_of_files;
    number_of_files = info_all_files_dir(path, &allfiles, error);

    if(my_collection.total_capacity == 0){
        *error = ERR_NO_COLLECTION;
        return my_collection;
    }
    if (number_of_files > INI_SIZE){
        *error = MORE_FILES_THAN_SPACE;
    }
    if(number_of_files == -1){
        *error = ERR_NO_COLLECTION;
        printf("No such directory\n");
        return my_collection;
    }

    int i;
    for ( i = 0; i < number_of_files; ++i){

        my_collection = add_file(my_collection, path, allfiles[i]->d_name, error);
    }
    free_info_files_array(allfiles,number_of_files);

    *error = SUCCESS_INPUT;

    return my_collection;
 }


int buscar_item_nombre(struct collection my_collection, char *nombre, int *error){
    int i;
    int encontrado= -1;

    if(my_collection.total_capacity == 0){
        *error = ERR_NO_COLLECTION;
        return -1;
    }
    for (i = 0; i < my_collection.number_occupied; i++) {
        if( strcmp(my_collection.tabla[i].data.filename, nombre) == 0)
            encontrado = 0;
    }
    *error = SUCCESS_INPUT;

    return encontrado;
}

int buscar_item_id(struct collection my_collection, int id, int *error){

    int i;
    int encontrado = -1;

    if(my_collection.number_occupied == 0){
        *error = ERR_NO_COLLECTION;
        return -1;
    }

    for (i= 0; i < my_collection.number_occupied; i++){
        if(my_collection.tabla[i].id == id)
            encontrado = i;
    }
    *error = SUCCESS_INPUT;
    return encontrado;

}

struct collection delete_item_id(struct collection my_collection, int id, int *errnum){

    if(my_collection.total_capacity == 0){
        *errnum = ERR_NO_COLLECTION;
        return my_collection;
    }

    int position = buscar_item_id(my_collection, id, errnum);
    if(position == -1){
        *errnum = ELEMENT_NOT_FOUND;
        return my_collection;
    }
    else{
        free_item(&my_collection.tabla[position]);

        int i;
        for (i = position ; i < my_collection.number_occupied; i++)
        {
            my_collection.tabla[i] = my_collection.tabla[i+1];
        }
        my_collection.number_occupied--;
        *errnum = SUCCESS_INPUT;

        return my_collection;
    }

}

struct collection sort_collection(struct collection my_collection, int (*compare)(const void *, const void *)){

    if(my_collection.number_occupied == 0){
        printf("There are no items in the collection to sort\n");
        return my_collection;
    }
    qsort(my_collection.tabla ,my_collection.number_occupied, sizeof(struct item),compare);
    return my_collection;
}

void print_item_id(struct collection my_collection, int id, int *errnum){

    if(my_collection.number_occupied == 0){
        *errnum = ERR_NO_COLLECTION;
        return;
    }

    int position = buscar_item_id(my_collection, id, errnum);
    if(position < 0){
        *errnum = ELEMENT_NOT_FOUND;
        return;
    }
    *errnum = SUCCESS_INPUT;
    
    printf(" Id      Inode       Perms       Links    Owner  Group  Size  Last Modification           Filename\n");
    print_item(my_collection.tabla[position]);
}


void print_collection(struct collection my_collection){

    if(my_collection.number_occupied == 0){
        printf("%s\n", get_error_msg_collection(ERR_NO_COLLECTION));
        return;
    }

    int i;

    printf(" Id      Inode       Perms       Links    Owner  Group  Size       Last Modification              Filename\n");

    for (i = 0; i < my_collection.number_occupied;i++)
    {
             print_item(my_collection.tabla[i]);
    }
}
