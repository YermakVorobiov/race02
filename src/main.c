#include "header.h"

int main(int argc, char *argv[]){
	if(argc != 6){
        write(2,"usage: ./way_home [file_name] [x1] [y1] [x2] [y2]\n", mx_strlen("usage: ./way_home [file_name] [x1] [y1] [x2] [y2]\n"));
        return 0;
    }
    char a;
    
    int file = open(argv[1], O_RDONLY);
    if(file == -1) 
    {
        write(2,"map doesn't exist\n",mx_strlen("map doesn't exist\n"));
        return 0;
    }
    else
    {
        if(read(file,&a,1) == 0) 
        {
            write(2,"map doesn't exist\n",mx_strlen("map doesn't exist\n"));
            return 0;
        }   
    }
    int lengthMazeX = 0;
    int lengthMazeY = 0;
    
    int y1 = mx_atoi(argv[3]);
    int x1 = mx_atoi(argv[2]);
    int y2 = mx_atoi(argv[5]);
    int x2 = mx_atoi(argv[4]);
    
    while(read(file,&a,1) > 0 && a != '\n')
    {
        if(a != ',')
        {
            lengthMazeX++;
        }
    }
    close(file);
    
    file = open(argv[1], O_RDONLY);
    
    while(read(file,&a,1) > 0)
    {
        if(a == '\n')
        {
            lengthMazeY++;
        }
    }
    close(file);
        if (x1 > lengthMazeX || y1 > lengthMazeY || x2 > lengthMazeX || y2 > lengthMazeY)
    {
        write(2, "points are out of map range\n", mx_strlen("points are out of map range\n"));
        return 0;
    }
    char **arr = (char **)malloc(lengthMazeY * sizeof(char *));
    for(int i = 0; i < lengthMazeY; i++){
    	arr[i] = mx_strnew(lengthMazeX);
    }
    char **arrPass = (char **)malloc(lengthMazeY * sizeof(char *));
    for(int i = 0; i < lengthMazeY; i++){
    	arrPass[i] = mx_strnew(lengthMazeX);
    }
    file = open(argv[1], O_RDONLY);
	for(int i = 0; i < lengthMazeY; i++){
		for(int j = 0; j < lengthMazeX; j++){
			if(read(file,&a,1) > 0){
				if(a == '#' || a == '.'){
					arr[i][j] = a;
					arrPass[i][j] = a;
				}
				else{
					j--;
				}
			}
		}
	}
    close(file);
   if (arr[y1][x1] == '#')
    {
        
        write(2, "entry point cannot be an obstacle\n", mx_strlen("entry point cannot be an obstacle\n"));
        return 0;
    }
    if (arr[y2][x2] == '#')
    {
        write(2, "exit point cannot be an obstacle\n", mx_strlen("exit point cannot be an obstacle\n"));
        return 0;
    }
     for (int i = 0; i != lengthMazeY; i++)
    {
        for (int j = 0; j != lengthMazeX; j++)
        {
            if (arr[i][j] == '.' || arr[i][j] == '#' || arr[i][j] == '\n')
            {
                continue;
            }
            else
            {
                write(2, "map error\n", mx_strlen("map error\n"));
                return 0;
            }
        }
    }
    	int Maxpoint = 0;
	for(int i = 0; i < lengthMazeY; i++){
		for(int j = 0; j < lengthMazeX; j++){
			if((char)arr[i][j] == '.'){
				Maxpoint++;
			}
		}
	}
	int currentElem = 50;
	arr[x1][y1] = currentElem;
	for(int a = 0; a < Maxpoint; a++){
	    	for(int i = 0; i < lengthMazeY; i++){
			for(int j = 0; j < lengthMazeX; j++){
				if(arr[i][j] == currentElem){
					if(i + 1 < lengthMazeY && arr[i + 1][j] == '.' && arr[i + 1][j] != '#'){
						arr[i + 1][j] =  currentElem + 1;
						}
					if(i - 1 > 0 && arr[i - 1][j] == '.' && arr[i - 1][j] != '#'){
						arr[i - 1][j] =  currentElem + 1;
						}
					if(j + 1 < lengthMazeX && arr[i][j + 1] == '.' && arr[i][j + 1] != '#'){
						arr[i][j + 1] =  currentElem + 1;
						}
					if(j - 1 > 0 && arr[i][j - 1] == '.' && arr[i][j - 1] != '#'){
						arr[i][j - 1] =  currentElem + 1;
						}
				}
			}
		}
		currentElem++;
	}
	
	int maxElem = 0;
	for(int i = 0; i < lengthMazeY; i++){
		for(int j = 0; j < lengthMazeX; j++){
			if(arr[i][j] > maxElem){
				maxElem = arr[i][j];
			}
		}
	}
	int Max = maxElem - 50;
	int Dis = arr[y2][x2] - 50;
	if(Max == Dis)
    {
        arrPass[y2][x2] = 'X';
    }
    else
    {
        arrPass[y2][x2] = '*';
    }
	if(Dis < 0)
	    {
		write(2, "route not found\n", 16);
		return 0;
	    }
	mx_printstr("dist=");
    mx_printint(Max);
    mx_printchar('\n');
    mx_printstr("exit=");
    mx_printint(Dis);
    mx_printchar('\n');
    
    
    char currentMove = arr[y2][x2];
    int move = 0;
    for(int i = y2, j = x2, k = 0; k < Dis; k++)
    {
        switch(move)
        {
            case 0:
                if(arr[i-1][j] == currentMove)
                {
                    arr[i-1][j] = '*';
                    arrPass[i-1][j] = '*';
                    i--;
                    move = 0;
                }
                else if(arr[i][j+1] == currentMove)
                {
                    arr[i][j+1] = '*';
                    arrPass[i][j+1] = '*';
                    j++;
                    move = 1;
                }
                else if(arr[i][j-1] == currentMove)
                {
                    arr[i][j-1] = '*';
                    arrPass[i][j-1] = '*';
                    j--;
                    move = 2;
                }
                else if(arr[i+1][j] == currentMove)
                {
                    arr[i+1][j] = '*';
                    arrPass[i+1][j] = '*';
                    i++;
                    move = 3;
                }
            break;
            case 3:
                if(arr[i+1][j] == currentMove)
                {
                    arr[i+1][j] = '*';
                    arrPass[i+1][j] = '*';
                    i++;
                    move = 0;
                }
                else if(arr[i][j-1] == currentMove)
                {
                    arr[i][j-1] = '*';
                    arrPass[i][j-1] = '*';
                    j--;
                    move = 1;
                }
                else if(arr[i][j+1] == currentMove)
                {
                    arr[i][j+1] = '*';
                    arrPass[i][j+1] = '*';
                    j++;
                    move = 2;
                }
                else if(arr[i-1][j] == currentMove)
                {
                    arr[i-1][j] = '*';
                    arrPass[i-1][j] = '*';
                    i--;
                    move = 3;
                }
            break;
            case 1:
                if(arr[i][j+1] == currentMove)
                {
                    arr[i][j+1] = '*';
                    arrPass[i][j+1] = '*';
                    j++;
                    move = 1;
                }
                else if(arr[i+1][j] == currentMove)
                {
                    arr[i+1][j] = '*';
                    arrPass[i+1][j] = '*';
                    i++;
                    move = 3;
                }
                else if(arr[i-1][j] == currentMove)
                {
                    arr[i-1][j] = '*';
                    arrPass[i-1][j] = '*';
                    i--;
                    move = 0;
                }
                else if(arr[i][j-1] == currentMove)
                {
                    arr[i][j-1] = '*';
                    arrPass[i][j-1] = '*';
                    j--;
                    move = 2;
                }
            break;
            case 2:
                if(arr[i][j-1] == currentMove)
                {
                    arr[i][j-1] = '*';
                    arrPass[i][j-1] = '*';
                    j--;
                     move = 2;
                }
                else if(arr[i-1][j] == currentMove)
                {
                    arr[i-1][j] = '*';
                    arrPass[i-1][j] = '*';
                    i--;
                    move = 0;
                }
                else if(arr[i+1][j] == currentMove)
                {
                    arr[i+1][j] = '*';
                    arrPass[i+1][j] = '*';
                    i++;
                    move = 3;
                }
                else if(arr[i][j+1] == currentMove)
                {
                    arr[i][j+1] = '*';
                    arrPass[i][j+1] = '*';
                    j++;
                    move = 1;
                }
            break;
        }
        currentMove -= 1;
    }
    arrPass[y1][x1] = '*';
    for(int i = 0; i < lengthMazeY; i++)
    {
        for(int j = 0; j < lengthMazeX; j++)
        {
            if(arr[i][j] == maxElem && arrPass[i][j] != 'X')
            {
                arrPass[i][j] = 'D';
            }
        }
    }
    int fileResult = open("path.txt", O_WRONLY);
    if (fileResult < 0)
    {
        fileResult = open("path.txt", O_CREAT | O_WRONLY);
    }
    for (int i = 0; i < lengthMazeY; i++)
    {
        for (int j = 0; j < lengthMazeX; j++)
        {
            char b = arrPass[i][j];
            write(fileResult, &b, 1);
        }
        write(fileResult, "\n", 1);
    }
    if(close(fileResult) < 0)
    {
        write(2, "error\n", 6);
    }
    return 0;
}
