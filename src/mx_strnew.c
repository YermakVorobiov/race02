#include <stdio.h>
#include <stdlib.h>

char *mx_strnew(const int size){
	if(size < 0){
		return NULL;
	}
	else{
		char *new = malloc(size+1);
		for(int i =0; i <= size; i++){
			new[i] = '\0';
		}
		return new;
	}
}


