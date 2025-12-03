#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>


typedef struct s_bsq{
	int lines;
	int lenght;
	char empty;
	char obstacle;
	char full;
	char **map;
} t_bsq;


bool isDigit(int c){
	return (c >= '0' && c <= '9');
}

bool isPrintable(int c){
	return (c >=' ' && c <= 126);
}

void printMap(t_bsq* data){
	for(int i=0;i<data->lines;i++){
		printf("%s\n", data->map[i]);
	}
}

int min(int a, int b, int c){
	int min=a;
	if(c < a)
		min = c;
	if(b < a)
		min = b;
	return min;
}

void freeData(t_bsq* data){
	if(!data)
		return;
	if(data->map)
	{
		for(int i =0;i<data->lines;i++){
			free(data->map[i]);
		}
		free(data->map);
	}
	free(data);

}

bool parse(t_bsq* data, char* line){
	int i=0;
	int nbr = 0;
	i =-1;
	while(isDigit(line[i])){
		nbr = nbr *10  + line[i] -'0';
	}
	if(line[i])
		return(0);
	if(isPrintable(line[i]) && isPrintable(line[i+1]) && isPrintable(line[i+2])&& !line[i+3])
	{
		data->empty = line[i];
		data->obstacle = line[i+1];
		data->full = line[i+2];
		data->lines = nbr;
		printf("%d, '%c', '%c' , '%c'\n",data->lines, data->empty, data->obstacle, data->full );
	}
	else return false;
	return true;
}

bool parseLine(t_bsq *data, FILE* file)
{
	char* line = NULL;
	size_t n=0;
	ssize_t len=0;
	len = getline(&line, &n, file);
	if(len < 5 || line[len-1] != '\n')
		return (free(line), NULL);
	line[len-1] = '\0';
	if(!parse(data, line))
		return(free(line), 0);
	return(free(line), 1);
}
t_bsq* getData(char* filename){

	FILE* file = filename?fopen(filename, "r") : stdin;
	if(!file)
		return NULL;
	t_bsq *data = calloc(1, sizeof(t_bsq));
	if(!data)
		return NULL;
	if(!parseLine(data, file))
		return(free(data), NULL);

	data->map = calloc(data->lines, sizeof(char*));
	if(!data->map)
		return (free(data), NULL);
	char *line;
	size_t n= 0;
	ssize_t len=0;
	for(int i=0;i<data->lines;i++){
		line =NULL;
		len = getline(&line, &n, file);
		if(len<1 || line[len-1] != '\n')
			return (free(line),freeData(data), NULL);
		line[len-1] = '\0';
		if(i==0)
			data->lenght = len-1;
		if((int)len-1 != data->lenght)
			return(free(line), freeData(data), NULL);
		data->map[i] = line;
	}
	fclose(file);
	return data;

}

bool checkData(t_bsq *data){
	if(!data)
		return 0;
	if(data->lines < 1 || data->lenght < 1)
		return (freeData(data), false);
	if(data->empty == data->obstacle || data->obstacle == data->full || data->full == data->empty)
		return (freeData(data), 0);
	for(int i=0; i< data->lines; i++){
		for(int j=0;j<data->lenght;j++){
			if(data->map[i][j] != data->empty && data->map[i][j] != data->obstacle)
				return (freeData(data), 0);
		}
	}
	return 1;
}

t_bsq* locig(t_bsq* data){
	int **map = calloc(data->lines, sizeof(int*));
	int max_i =0, max_j=0,max_size=0;

	for(int i=0;i<data->lines;i++){
		map[i] = calloc(data->lenght, sizeof(int));
		for(int j=0;j<data->lenght;j++){
			if(!i || !j)
				map[i][j] = 1;
			else if(map[i][j] == data->obstacle)
				map[i][j] = 0;
			else if(i>0&&j>0)
				map[i][j] = min(map[i-1][j], map[i][j-1], map[i-1][j-1]);
			if(map[i][j]>max_size){
				max_size=map[i][j];
				max_i=i;
				max_j=j;
			}
		}
	}

	for(int i=0; i < data->lines;i++)
		free(map[i]);
	free(map);

	for(int i=max_i -(max_size -1);i<= max_i;i++){
		for(int j=max_j - (max_size-1);j<= max_j;j++){
			data->map[i][j] = data->full;
		}
	}
	return data;
}


void parseInput(char *filename){
	t_bsq* data = getData(filename);
	if(!checkData(data))
	{
		printf("Error: invalid map\n");
		return;
	}
	data = locig(data);
	printMap(data);
	freeData(data);
}

int main(int ac, char** av)
{
	if(ac == 1)
		parseInput(NULL);
	else if(ac == 2)
		parseInput(av[1]);
	else
		printf("Error: invalid args");
}