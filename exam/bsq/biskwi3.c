#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct bsq{
	int lines;
	int lenght;
	char empty;
	char obstacle;
	char full;

	char** map;
}t_bsq;



bool isDigit(int c){
	return (c >= '0' && c<='9');
}

bool isPrintable(int c){
	return (c >=' ' && c <= 126);
}

void freeData(t_bsq* data){
	if(!data)
		return;
	if(data->map)
	{
		for (int i = 0; i < data->lines; i++)
			free(data->map[i]);
		free(data->map);
	}
	free(data);
}

void printMap(t_bsq* data){
	for (int i = 0; i < data->lines; i++)
	{
		printf("%s\n", data->map[i]);
	}
}

int min(int a, int b, int c){
	int min = a;
	if(b < min)
		min = b;
	if(c < min)
		min=c;
	return min;
}

bool parse(t_bsq* data, char* line){
	int nbr=0;
	int i =0;
	while(isDigit(line[i]))
	{
		nbr = nbr * 10 + line[i] - '0';
		i++;
	}
	if(!line[i])
		return 0;
	if(isPrintable(line[i]) && isPrintable(line[i+1]) && isPrintable(line[i+2]) && !line[i+3])
	{
		data->lines = nbr;
		data->empty = line[i];
		data->obstacle = line[i+1];
		data->full = line[i+2];
		return true;
	}
	return false;

}

bool parseLine(t_bsq* data, FILE* file){
	char* line = NULL;
	size_t n=0;
	ssize_t len = 0;
	len = getline(&line, &n, file);
	if(len < 5|| line[len-1] != '\n')
		return(free(line), 0);
	line[len-1] = '\0';
	if(!parse(data, line))
		return(free(line), false);
	return (free(line), true);
}

t_bsq *getData(char *input){
	FILE* file = input? fopen(input, "r") : stdin;
	if(!file)
		return NULL;
	t_bsq* data = calloc(1, sizeof(t_bsq));
	if(!data)
		return(fclose(file), NULL);
	if(!parseLine(data, file))
		return(fclose(file), free(data), NULL);
	data->map = calloc(data->lines+1, sizeof(char *));
	if(!data->map)
		return(fclose(file), free(data), NULL);
	char *line;
	size_t n=0;
	ssize_t len=0;
	for(int i=0;i<data->lines;i++){
		line = NULL;
		len = getline(&line, &n, file);
		if(len < 1||line[len -1] != '\n')
			return(free(line), freeData(data), NULL);
		line[len-1] = '\0';
		if(i == 0)
			data->lenght = len-1;
		if(data->lenght != (int) len-1)
			return(free(line), freeData(data), NULL);
		data->map[i] = line;
	}
	return data;
}

bool checkData(t_bsq *data){
	if(!data)
		return 0;

	if(data->lines < 1 || data->lenght < 1)
		return(freeData(data), false);
	if(data->empty == data->obstacle || data->obstacle == data->full || data->full == data->empty)
		return(freeData(data), false);
	for (int i = 0; i < data->lines; i++)
	{
		for (int j = 0; j < data->lenght; j++)
		{
			if(data->map[i][j] != data->empty && data->map[i][j] != data->obstacle)
				return (freeData(data),false);
		}

	}
	return true;
}

t_bsq *logic(t_bsq*	data){
	int **imap=calloc(data->lines, sizeof(int*));
	int imax = 0, jmax = 0, maxsize = 0;
	for (int i = 0; i < data->lines; i++)
	{
		imap[i] = calloc(data->lenght, sizeof(int));
		for (int j = 0; j < data->lenght; j++)
		{
			if(data->map[i][j] == data->obstacle)
				imap[i][j] = 0;
			else if(!i || !j)
				imap[i][j] = 1;
			else
				imap[i][j] = min(imap[i-1][j], imap[i][j-1],imap[i-1][j-1]) + 1;
			if(imap[i][j] > maxsize)
			{
				maxsize = imap[i][j];
				imax = i;
				jmax = j;
			}
		}
	}
	for(int i=0;i<data->lines;i++){
		free(imap[i]);
	}
	free(imap);

	for (int i = imax - maxsize+1; i <= imax; i++)
	{
		for (int j = jmax - maxsize +1; j <= jmax; j++)
		{
			data->map[i][j] = data->full;
		}

	}
	return data;


}

void processInput(char* input){
	t_bsq* data = getData(input);
	if(!checkData(data))
	{
		printf("Error: invalid map!\n");
		return;
	}
	data = logic(data);
	printMap(data);
	freeData(data);
}


int main(int ac, char **av){
	if(ac == 1)
		processInput(NULL);
	else if(ac == 2)
		processInput(av[1]);
	else
		printf("Bad arguments!");
}