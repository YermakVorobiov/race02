#include <stdbool.h>

int mx_atoi(const char *str){
	int sum = 0;	
	for(int i = 0; str[i] != '\0'; i++){

		if(str[i] == ' ' 
	   	   || str[i] == '\r' 
	   	   || str[i] == '\t' 
	           || str[i] == '\n'
	   	   || str[i] == '\v'
	   	   || str[i] == '\f'){
			continue;
		}
		if(48 <= str[i] && str[i] <= 57){
			sum = sum * 10 + str[i] - 48;
		}
		else{
			return 0;
		}
	}
	if(str[0] == '-'){
		sum *= -1;
	}
	return sum;
}

