#include "util_files.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//char actualpath [PATH_MAX+1] -> abs_filename


int info_file(char *path, char *filename, char **abs_filename, struct stat *bufStat){

	char actualpath[PATH_MAX+1];

	if(realpath(path, actualpath) == NULL){
		return errno;
	}

	strcat(actualpath, "/");
	strcat(actualpath, filename);

	if(abs_filename == NULL){
		return errno;
	}

	if(lstat(filename, bufStat) != 0){
		return errno;
	}
	*abs_filename = strdup(actualpath);
	
	return 0;

}

/* SANDRA & HBIBI 
int info_file(char *path, char *filename, char **abs_filename, struct stat *bufStat){

	char actualpath[PATH_MAX+1];

	*abs_filename = malloc(sizeof(char)*PATH_MAX);

	if(realpath(path, actualpath) == NULL){
		return errno;
	}

	strcat(actualpath, "/");
	strcat(actualpath, filename);


	if(abs_filename == NULL){
		return errno;
	}

	if(lstat(filename, bufStat) != 0){
		return errno;
	}
	*abs_filename = strdup(actualpath);

	return 0;

}*/
