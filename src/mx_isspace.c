#include <stdbool.h>

bool mx_isspace(char c){
	if(c == ' ' 
	   || c == '\r' 
	   || c == '\t' 
	   || c == '\n'
	   || c == '\v'
	   || c == '\f'){
		return 1;
	}
	return 0;
}



