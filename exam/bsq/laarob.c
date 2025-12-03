#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>


typedef struct s_bsq
{

    int lines;
    int length;

    char empty;
    char obstacle;
    char full;

    char **map;

}   t_bsq;

int min3(int a, int b, int c)
{
    int min = a;
    if (b < min)
        min = b;
    if (c < min)
        min = c;
    return (min);
}


bool isDig(int c)
{
    return (c >= '0' && c <= '9');
}

bool isPrint(int c)
{
    return (c >= ' ' && c <= '~');
}

void    printMap(t_bsq *data)
{
    for (int i = 0; i < data->lines; i++)
        printf("%s\n", data->map[i]);
}

void freeData(t_bsq *data)
{
    int i = -1;
    while (data->map[++i])
        free(data->map[i]);
    free(data->map);
    free(data);
}


bool parse(t_bsq *data, char *line)
{
    int i = 0;
    int nbr = 0;

    while (isDig(line[i]))
    {
        nbr = nbr * 10 + line[i] - '0';
        i++;
    }
    if (!line[i])
        return false;


    if(isPrint(line[i]) && isPrint(line[i + 1]) && isPrint(line[i + 2]) && !line[i + 3])
    {
        data->empty = line[i];
        data->obstacle = line[i + 1];
        data->full = line[i + 2];
        data->lines = nbr;
	    printf("%d, '%c', '%c' , '%c'\n",data->lines, data->empty, data->obstacle, data->full );

    }
    else
        return false;
    return true;
}


bool parseLine(t_bsq *data, FILE *file)
{
    char *line = NULL;
    size_t n = 0;
    ssize_t len = 0;

    len = getline(&line, &n, file);
    if (len < 5 || line[len - 1] != '\n')
        return (free(line), false);
    line[len - 1] = '\0';
    if (!parse(data, line))
        return (free(line), false);
    return (free(line), true);
}

t_bsq *logic(t_bsq *data)
{
	int imap[data->lines][data->length];
	int x = 0, y = 0, max = 0;

	for(int i = 0; i < data->lines; i++)
	{
		for(int j = 0; j < data->length; j++)
		{
			if (data->map[i][j] == data->obstacle)
				imap[i][j] = 0;
			else if (!i || !j)
				imap[i][j] = 1;
			else
				imap[i][j] = min3(imap[i - 1][j], imap[i][j - 1], imap[i - 1][j - 1]) + 1;
			if (imap[i][j] > max)
			{
				x = i;
				y = j;
				max = imap[i][j];
			}
		}
	}
	for (int i = x - max + 1; i < x; i++)
	{
		for (int j = y - max + 1; j < y; j++)
			data->map[i][j] = data->full;
	}
	return (data);
}

t_bsq *getData(char *input)
{
    FILE *file = input ? fopen(input, "r") : stdin;
    if (!file)
        return (NULL);

    t_bsq *data = calloc(1, sizeof(t_bsq));
    if(!data)
        return NULL;//////
    if (!parseLine(data, file))
        return free(data), NULL; /////


        data->map = calloc(data->lines + 1, sizeof(char *));
    if (!data->map)
        return (free(data), NULL);

    char *line;
    size_t n = 0;
    ssize_t len = 0;

    for (int i = 0; i < data->lines; i++)
    {
        line = NULL;
        len = getline(&line, &n, file);

        if (len < 1 || line[len - 1] != '\n')
            return (free(line), freeData(data), NULL);
        line[len - 1] = '\0';
        if (i == 0)
            data->length = len - 1;
        if (data->length != (int)len - 1)
            return (free(line), freeData(data), NULL);
        data->map[i] = line;
    }
    fclose(file);
    return data;
}

bool checkData(t_bsq *data)
{
    if (!data)
        return false;
    if (data->lines < 1 || data->length < 1)
        return (freeData(data), false);
    if (data->empty == data->obstacle || data->obstacle == data->full || data->full == data->empty)
        return (freeData(data), false);

    for(int i = 0; i < data->lines; i++)
    {
        for(int j = 0; j < data->length; j++)
            if (data->map[i][j] != data->empty && data->map[i][j] != data->obstacle)
                return (freeData(data), false);
    }
    return true;
}


void    parseInput(char *input)
{
    t_bsq *data = getData(input);
    if (!checkData(data))
    {
        printf("Error: invalid map\n");
        return;
    }
    // // data = logic(data);
    printMap(data);
    freeData(data);
}

int main(int ac, char **av)
{
    if (ac == 1)
        parseInput(NULL);
    else if (ac == 2)
        parseInput(av[1]);
    else
        printf("Error: invalid map\n");
}
