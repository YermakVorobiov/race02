#include <stdbool.h>
#include <unistd.h>

void mx_printint(int n){
	int buffer[10];
	int i = 0;
	char last[i];
	char minus = '-';
	if (n < 0) {
		n *= -1;
		write(1,&minus,1);
	}
	while (n != 0) {
		buffer[i]= n % 10;
		n = n / 10;
		last[i] = 48 + buffer[i];
		i++;
	}
	for (int j = i-1; j >= 0; j--) {
		write(1,&last[j],1);
	}
}

