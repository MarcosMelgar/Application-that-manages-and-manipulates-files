#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <unistd.h>
#include "item.h"
#include "util_files.h"
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define LTIME 30




struct item create_item(char *path, char *filename, char *abs_filename, struct stat info,int *error){

	struct item my_item;

	my_item.data.filename = (char *) malloc(sizeof(char)*(strlen(filename)+1));
	if (my_item.data.filename == NULL)
	{
		*error = errno;
		return my_item;
	}
	strcpy(my_item.data.filename, filename);

	my_item.data.path = (char *) malloc(sizeof(char)*(strlen(path)+1));
	if (my_item.data.path == NULL)
	{
		*error = errno;
		return my_item;
	}
	strcpy(my_item.data.path, path);
	
	my_item.data.abs_filename = (char *) malloc(sizeof(char)*(strlen(abs_filename)+1));
	if (my_item.data.abs_filename == NULL)
	{
		*error = errno;
		return my_item;
	}	
	strcpy(my_item.data.abs_filename, abs_filename);

	my_item.data.st_ino = info.st_ino;
	my_item.data.st_size = info.st_size;
	my_item.data.st_nlink = info.st_nlink;
	my_item.data.st_mtim = info.st_mtim;
	my_item.data.st_mode = info.st_mode;
	my_item.data.owner = info.st_uid;
	my_item.data.group = info.st_gid;

	//strdup
	my_item.data.owner_name = strdup(getpwuid(my_item.data.owner)->pw_name);
	my_item.data.group_name = strdup(getgrgid(my_item.data.group)->gr_name);

	//if it is a symbol link
	if(S_ISLNK(my_item.data.st_mode)){
		
		ssize_t bufsiz, r;
		bufsiz = info.st_size+1;
		if(info.st_size == 0)
			bufsiz = PATH_MAX;
		my_item.data.target_filename = (char *)malloc(sizeof(char)*bufsiz);
		if(my_item.data.target_filename == NULL){
			*error = errno;
			return my_item;
		}
		r = readlink(filename, my_item.data.target_filename, bufsiz);
		if(r == -1){
			*error = errno;
			return my_item;
		}
		my_item.data.target_filename[r] = '\0';	
	}else{
		my_item.data.target_filename = NULL;
	}
	return my_item;

}

void free_item(struct item *item){
	if(item == NULL)
		return;
	free(item->data.filename);
	free(item->data.path);
	free(item->data.abs_filename);
	free(item->data.owner_name);
	free(item->data.group_name);
	if(S_ISLNK(item->data.st_mode))
		free(item->data.target_filename);
}

void print_item(struct item foo){

	struct tm *t;
	char bufftime[LTIME];
  	t = localtime(&foo.data.st_mtime);
  	strftime(bufftime, LTIME, "%a %b %d %Y %T", t);
    char permisos[11] = {0,0,0,0,0,0,0,0,0,0,0};
	print_permissions(foo.data.st_mode, permisos, foo);
	printf("[%d]\t%ld     %s   %ld        %s   %s   %ld\t   %s\t  %s", foo.id, foo.data.st_ino, permisos, foo.data.st_nlink, foo.data.owner_name, foo.data.group_name, foo.data.st_size, bufftime , foo.data.filename);
	if(foo.data.target_filename != NULL){
		printf("->%s",foo.data.target_filename);
	}
	printf("\n");
}

char *print_permissions(mode_t st_mode, char *perms, struct item foo){
	strcat(perms, (st_mode & S_ISDIR(foo.data.st_mode)) ? "d" : "-");
	strcat(perms, (st_mode & S_IRUSR) ? "r" : "-");
    strcat(perms, (st_mode & S_IWUSR) ? "w" : "-");
    strcat(perms, (st_mode & S_IXUSR) ? "x" : "-");
    strcat(perms, (st_mode & S_IRGRP) ? "r" : "-");
    strcat(perms, (st_mode & S_IWGRP) ? "w" : "-");
    strcat(perms, (st_mode & S_IXGRP) ? "x" : "-");
    strcat(perms, (st_mode & S_IROTH) ? "r" : "-");
    strcat(perms, (st_mode & S_IWOTH) ? "w" : "-");
    strcat(perms, (st_mode & S_IXOTH) ? "x" : "-");
    return perms;
}

int compare_id(const void *p, const void *q){

	struct item *item1, *item2;
	
	item1 = (struct item *) p;
	item2 = (struct item *) q;

	if(item1->id > item2->id)
		return 1;
	else if(item1->id > item2->id)
		return -1;
	return 0;
}
int compare_filename(const void *p, const void *q){
	
	struct item *item1, *item2;
	
	item1 = (struct item *) p;
	item2 = (struct item *) q;

	if(strcmp(item1->data.filename, item2->data.filename) > 0)
		return 1;
	else if(strcmp(item1->data.filename, item2->data.filename) < 0)
		return -1;
	else
		return  0;
}

int compare_last_modified(const void *p, const void *q){

	struct item *item1, *item2;
	
	item1 = (struct item *) p;
	item2 = (struct item *) q;

	if(item1->data.st_mtime - item2->data.st_mtime > 0)
		return 1;
	else if(item1->data.st_mtime - item2->data.st_mtime < 0)
		return -1;
	return 0;

}

int compare_size(const void *p, const void *q){

	struct item *item1, *item2;
	
	item1 = (struct item *) p;
	item2 = (struct item *) q;

	if(item1->data.st_size - item2->data.st_size > 0)
		return 1;
	else if(item1->data.st_size - item2->data.st_size < 0)
		return -1;
	return 0;

}

int compare_inode(const void *p, const void *q){

	struct item *item1, *item2;
	
	item1 = (struct item *) p;
	item2 = (struct item *) q;

	if(item1->data.st_ino - item2->data.st_ino > 0)
		return 1;
	else if(item1->data.st_ino - item2->data.st_ino < 0)
		return -1;
	return 0;
}
