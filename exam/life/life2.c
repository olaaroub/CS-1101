#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int main(int ac, char **av){
	int w = atoi(av[1]), h = atoi(av[2]), it = atoi(av[3]);
	int map[h][w], next[h][w];
	bool pen = false;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
			map[i][j] = 0;

	}
	char c;
	int i=0, j =0;


	while(read(0, &c, 1))
	{
		if(c == 'x') pen =!pen;
		else if(c=='w' && i > 0) i--;
		else if(c == 's' && i < h-1) i++;
		else if(c == 'a' && j > 0) j--;
		else if(c == 'd' && j < w - 1 ) j++;
		if(pen)
			map[i][j] = 1;
	}
	for(int itr= 0; itr< it; itr++)
	{
		for(int i=0;i<h;i++){
			for(int j =0; j <w;j++){


				int n=0;
				for(int ih=-1; ih <=1; ih++)
				{
					for(int jw =-1;jw <= 1;jw++)
					{
						if((ih || jw)&& ((i+ih>=0&&i+ih<h) && (j+jw >= 0 && j+jw <w)))
							n+= map[i+ih][j+jw];
					}
				}
				next[i][j]=(map[i][j] && (n==3 || n==2)) || (!map[i][j] && n==3);
			}
		}
		for(int i=0;i<h;i++){
			for(int j=0; j<w;j++){
				map[i][j] = next[i][j];
			}
		}
	}

	for(int i = 0; i< h; i++){
		for(int j=0; j<w;j++)
			map[i][j] ? putchar('0'): putchar('-');
		putchar('\n');
	}
}