#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init_game(int *p1[10][10], int *p2[10][10], int *a[10][10])  // Initialize game fields, tree and fox positions
	// p1 - field with AI foxes for player;  p2 - massive with player's foxes for player;
	// a - field for AI algorithm
	// 0 - number for empty position, -1 - fox position, -2 - tree position, -3 - fox body position
{
	int i, j, tree_numb, x, y;
	for (i = 0; i < 10; i++)
		for (j = 0; j < 10; j++)
			p1[i][j] = p2[i][j] = a[i][j] = 0;
	srand(time(NULL));
	tree_numb = rand() % 3 + 2;      // Generating number of trees
	for (i = 0; i < tree_numb; i++)  // Generating tree positions for both player and AI (trees have the same positions)
	{
		x = rand() % 10;
		y = rand() % 10;
		if (p1[x][y] != -2)
			p1[x][y] = p2[x][y] = a[x][y] = -2;
		else i--;
	}
	for (i = 0; i < 10; i++)         // Generating fox positions for player
	{
		x = rand() % 10;
		y = rand() % 10;
		if ((p2[x][y] != -2) && (p2[x][y] != -1))
			p2[x][y] = a[x][y] = -1;
		else i--;
	}
	for (i = 0; i < 10; i++)         // Generating fox positions for AI
	{
		x = rand() % 10;
		y = rand() % 10;
		if ((p1[x][y] != -2) && (p1[x][y] != -1))
			p1[x][y] = -1;
		else i--;
	}
}

////////////////////////////////////////////////////
int main()
{
	int p1[10][10], p2[10][10], a[10][10];
	init_game(&p1, &p2, &a);
	int i, j, move_numb = 0;  // move_numb - number of moves have done since game starting
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
			printf("%-3d", p1[i][j]);
		printf("\n");
	}
	return 0;
}
