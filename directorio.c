#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <dirent.h>
#include "collection.h"
#include "util_files.h"
#include <errno.h>

int info_all_files_dir(char *path, struct dirent ***info_files, int *error){

	char actualpath[PATH_MAX+1];

	if(realpath(path, actualpath) == NULL){
		*error = errno;
	}
	
	int number_files = scandir(actualpath, info_files ,NULL ,alphasort);
	if(number_files < 0){
		*error = errno;
		return -1;
	}
	return number_files;
}


void free_info_files_array( struct dirent **info_files, int n){

	int i;
	for (i = 0; i < n;i++)
	{
		free(info_files[i]);
	}
	free(info_files);
}
