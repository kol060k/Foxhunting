#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int p1[10][10], p2[10][10], a[10][10];
					// p1 - field with AI foxes for player;  p2 - massive with player's foxes for player;
					// a - field for AI algorithm
int fox_number = 10, tree_number = 0;  // Number of foxes and trees in game

void init_game()  // Initialize game fields, tree and fox positions
	// p1 - field with AI foxes for player;  p2 - massive with player's foxes for player;
	// a - field for AI algorithm
	// 0 - number for empty position, -1 - fox position, -2 - tree position, -3 - fox body position
{
	int i, j, x, y;
	for (i = 0; i < 10; i++)
		for (j = 0; j < 10; j++)
			p1[i][j] = p2[i][j] = a[i][j] = 0;
	if (tree_number == 0) tree_number = rand() % 3 + 2;  // Generating number of trees if it's not set at the beginning
	for (i = 0; i < tree_number; i++)  // Generating tree positions for both player and AI (trees have the same positions)
	{
		x = rand() % 10;
		y = rand() % 10;
		if (p1[x][y] != -2)
			p1[x][y] = p2[x][y] = a[x][y] = -2;
		else i--;
	}
	for (i = 0; i < fox_number; i++)         // Generating fox positions for player
	{
		x = rand() % 10;
		y = rand() % 10;
		if ((p2[x][y] != -2) && (p2[x][y] != -1))
			p2[x][y] = -1;
		else i--;
	}
	for (i = 0; i < fox_number; i++)         // Generating fox positions for AI
	{
		x = rand() % 10;
		y = rand() % 10;
		if ((p1[x][y] != -2) && (p1[x][y] != -1))
			p1[x][y] = -1;
		else i--;
	}
}

int find_fox(int p[10][10], int m, int n)  // Function of searching foxes in strings, columns and diagonals
{
	int numb = 0, i, j;
	for (i = m - 1; i >= 0; i--)  // Going up
	{
		if (p[i][n] == -2) break;
		if (p[i][n] == -1) numb++;
	}
	for (i = m + 1; i < 10; i++)  // Going down
	{
		if (p[i][n] == -2) break;
		if (p[i][n] == -1) numb++;
	}
	for (j = n - 1; j >= 0; j--)  // Going left
	{
		if (p[m][j] == -2) break;
		if (p[m][j] == -1) numb++;
	}
	for (j = n + 1; j < 10; j++)  // Going right
	{
		if (p[m][j] == -2) break;
		if (p[m][j] == -1) numb++;
	}
	for (i = m - 1, j = n - 1; (i >= 0) && (j >= 0); i--, j--)  // Going up and left
	{
		if (p[i][j] == -2) break;
		if (p[i][j] == -1) numb++;
	}
	for (i = m + 1, j = n - 1; (i < 10) && (j >= 0); i++, j--)  // Going down and left
	{
		if (p[i][j] == -2) break;
		if (p[i][j] == -1) numb++;
	}
	for (i = m - 1, j = n + 1; (i >= 0) && (j < 10); i--, j++)  // Going up and right
	{
		if (p[i][j] == -2) break;
		if (p[i][j] == -1) numb++;
	}
	for (i = m + 1, j = n + 1; (i < 10) && (j < 10); i++, j++)  // Going down and right
	{
		if (p[i][j] == -2) break;
		if (p[i][j] == -1) numb++;
	}
	return numb;
}

int player_move(int a_foxleft)  // Function that works with player's turn
{
	int m = 0, n = 0, right_shot = 0;  // m, n - numbers of string and column; right_shot - checker if shot correct
									   ///////// Scan player's shot
	while (right_shot == 0)
	{
		printf("Enter coordinates, please.\n");
		while ((m < 1) || (m > 10))
		{
			printf("String number (1 - 10): ");
			scanf("%d", &m);
			if ((m < 1) || (m > 10)) printf("Enter number from 1 to 10\n");
		}
		while ((n < 1) || (n > 10))
		{
			printf("Column number (1 - 10): ");
			scanf("%d", &n);
			if ((n < 1) || (n > 10)) printf("Enter number from 1 to 10\n");
		}
		if ((p1[m - 1][n - 1] == 0) || (p1[m - 1][n - 1] == -1))
			right_shot = 1;
		else
		{
			printf("You can't shoot there\n");
			m = 0;
			n = 0;
		}
	}
	n--;
	m--;

	///////// Shooting
	if (p1[m][n] == 0) p1[m][n] = find_fox(p1, m, n);
	else
	{
		p1[m][n] = -3;
		a_foxleft--;
	}
	if (p1[m][n] == 0) p1[m][n] = -10;  // If there is no one foxes in string, column and diagonals, we still need to mark the cell that player shooted here
	return a_foxleft;
}

int add_value_a_1(int cell, int val)  // Add value to 1 cell
{
	if ((val > 0) && (cell >= 0)) cell = cell + val;  // If there are >0 foxes visible and cell empty then add value to cell
	if ((val == -1) && (cell > 0)) cell = cell + val;  // If fox killed, -1 to all cells in column, string and diagonals
	if (val == 0) cell = -10;  // -10 if no one fox in column, string or diagonals
	return cell;
}

void add_value_a(int m, int n)  // Add numbers to array a (need to algorithm)
{
	int i, j, val;
	val = find_fox(p2, m, n);
	if (a[m][n] == -1) val = -1;
	a[m][n] = -10;  // We can't shoot to this cell again, so just never look at it again
	for (i = m - 1; i >= 0; i--)  // Going up
	{
		if (a[i][n] == -2) break;
		a[i][n] = add_value_a_1(a[i][n], val);
	}
	for (i = m + 1; i < 10; i++)  // Going down
	{
		if (a[i][n] == -2) break;
		a[i][n] = add_value_a_1(a[i][n], val);
	}
	for (j = n - 1; j >= 0; j--)  // Going left
	{
		if (a[m][j] == -2) break;
		a[m][j] = add_value_a_1(a[m][j], val);
	}
	for (j = n + 1; j < 10; j++)  // Going right
	{
		if (a[m][j] == -2) break;
		a[m][j] = add_value_a_1(a[m][j], val);
	}
	for (i = m - 1, j = n - 1; (i >= 0) && (j >= 0); i--, j--)  // Going up and left
	{
		if (a[i][j] == -2) break;
		a[i][j] = add_value_a_1(a[i][j], val);
	}
	for (i = m + 1, j = n - 1; (i < 10) && (j >= 0); i++, j--)  // Going down and left
	{
		if (a[i][j] == -2) break;
		a[i][j] = add_value_a_1(a[i][j], val);
	}
	for (i = m - 1, j = n + 1; (i >= 0) && (j < 10); i--, j++)  // Going up and right
	{
		if (a[i][j] == -2) break;
		a[i][j] = add_value_a_1(a[i][j], val);
	}
	for (i = m + 1, j = n + 1; (i < 10) && (j < 10); i++, j++)  // Going down and right
	{
		if (a[i][j] == -2) break;
		a[i][j] = add_value_a_1(a[i][j], val);
	}
}

int random_shoot(int p_foxleft)  // Starting random AI shots
{
	int m, n, right_shot = 0;  // m, n - numbers of string and column; right_shot - checker if shot correct
	while (right_shot == 0)
	{
		m = rand() % 10;
		n = rand() % 10;
		if ((p2[m][n] == 0) || (p2[m][n] == -1))
			right_shot = 1;
	}
	if (p2[m][n] == 0)
	{
		p2[m][n] = find_fox(p2, m, n);
		add_value_a(m, n);
	}
	else
	{
		a[m][n] = -10;
		p2[m][n] = -3;
		p_foxleft--;
	}
	if (p2[m][n] == 0) p2[m][n] = -10;  // If there is no one foxes in string, column and diagonals, we still need to mark the cell that player shooted here
	printf("AI shot.\n");
	printf("String: %d\n", m + 1);
	printf("Column: %d\n", n + 1);
	return p_foxleft;
}

int AI_shoot(int p_foxleft)  // Function works with AI shots
// AI finds the cells with biggest numbers in array a (biggest numbers means bigest chance of fox there) and shoot to random biggest cell
{
	int cells[2][100];  // Array with biggest cells. cells[0][i] = m, cells[1][i] = n
	int max = 0, numb = 0, shoot_cell, i, j, m, n;  // max - maximal cell value in array a, numb - number of biggest cells, shoot_cell - cell, chosen for shoot
	for (i = 0; i < 10; i++)
		for (j = 0; j < 10; j++)
			if (a[i][j] >= 0)
				if (a[i][j] > max)
				{
					numb = 1;
					max = a[i][j];
					cells[0][0] = i;
					cells[1][0] = j;
				}
				else if (a[i][j] == max)
				{
					cells[0][numb] = i;
					cells[1][numb] = j;
					numb++;
				}
	shoot_cell = rand() % numb;
	m = cells[0][shoot_cell];
	n = cells[1][shoot_cell];
	if (p2[m][n] == -1)
	{
		a[m][n] = -10;
		p_foxleft--;
		p2[m][n] = -3;
	}
	else
	{
		p2[m][n] = find_fox(p2, m, n);
		add_value_a(m, n);
	}
	if (p2[m][n] == 0) p2[m][n] = -10;  // If there is no one foxes in string, column and diagonals, we still need to mark the cell that player shooted here
	printf("AI shot.\n");
	printf("String: %d\n", m + 1);
	printf("Column: %d\n", n + 1);
	return p_foxleft;
}


void print(int p1[10][10], int p2[10][10])  // Printing of fields
// F - Fox, T - Tree, X - fox body, . - closed cell, 0 - fox_number - number of foxes in string, column and diagonals
{
	int i, j, x;
	printf("Opponent:                   You:\n");
	printf("    1 2 3 4 5 6 7 8 9 10        1 2 3 4 5 6 7 8 9 10\n");
	for (i = 1; i <= 10; i++)
	{
		///////// Opponent field
		printf("%-3d", i);
		for (j = 1; j <= 10; j++)
		{
			x = p1[i - 1][j - 1];
			switch (x)
			{
			case -1:
				printf(" .");  // Hide opponent's foxes
				break;
			case -2:
				printf(" T");
				break;
			case -3:
				printf(" X");
				break;
			case -10:
				printf(" 0");
				break;
			case 0:
				printf(" .");
				break;
			default:
				printf("%2d", x);
			}
		}

		/////////// Your field
		printf("     ");
		printf("%-3d", i);
		for (j = 1; j <= 10; j++)
		{
			x = p2[i - 1][j - 1];
			switch (x)
			{
			case -1:
				printf(" F");
				break;
			case -2:
				printf(" T");
				break;
			case -3:
				printf(" X");
				break;
			case -4:
				printf(" X");
				break;
			case -10:
				printf(" 0");
				break;
			case 0:
				printf(" .");
				break;
			default:
				printf("%2d", x);
			}
		}
		printf("\n");
	}
}

/////////////////MAIN///////////////////////////////
int main()
{
	printf("Enter number of foxes in field (>0): ");  // You can change number of foxes at the beginning
	scanf("%d", &fox_number);
	if (fox_number <= 0) fox_number = 10;
	printf("Enter number of trees in field (0 - randomly generating): ");  // You can change number of trees at the beginning
	scanf("%d", &tree_number);
	srand(time(NULL));
	init_game();
	int move_numb = 0, beg_shots = 0;  // move_numb - number of moves have done since game starting, beg_shots - number of random shots AI did at the beginning
	int p_foxleft = fox_number, p_foxleft1 = fox_number, a_foxleft = fox_number, a_foxleft1 = fox_number;  // Number of player's/AI foxes left 
	int i, j;
	printf("\nBattle begins!\n");
	printf("	You have %d foxes alive.\n", p_foxleft);
	printf("	AI have %d foxes alive.\n", a_foxleft);
	print(p1, p2);

	while ((p_foxleft > 0) && (a_foxleft > 0))
	{
		////////// Player's move
		a_foxleft = player_move(a_foxleft);
		print(p1, p2);
		while ((a_foxleft < a_foxleft1) && (a_foxleft > 0))  // If fox killed, repeat move (untill killing series ending or killing all the foxes)
		{
			a_foxleft1 = a_foxleft;
			a_foxleft = player_move(a_foxleft);
			print(p1, p2);
		}
		if (a_foxleft == 0)  // Check number of foxes. If it = 0, finish the game
		{
			printf("CONGRATULATIONS!\n");
			printf("YOU WON!\n");
			printf("You have %d foxes alive.\n", p_foxleft);
			break;
		}

		////////// AI move
		if (beg_shots < 3)  // AI need to do some starting random shots
			p_foxleft = random_shoot(p_foxleft);
		else
			p_foxleft = AI_shoot(p_foxleft);
		print(p1, p2);
		while ((p_foxleft < p_foxleft1) && (p_foxleft > 0))  // If fox killed, repeat move
		{
			p_foxleft1 = p_foxleft;
			if (beg_shots < 3)
				p_foxleft = random_shoot(p_foxleft);
			else
				p_foxleft = AI_shoot(p_foxleft);
			print(p1, p2);
		}
		if (beg_shots < 3) beg_shots++;
		if (p_foxleft == 0)  // Check fox number. Finish the game if it = 0
		{
			printf("You lost to AI!\n");
			printf("AI have %d foxes alive.\n", a_foxleft);
			printf("AI has become smarter than man!\n");
			printf("The enslavement of mankind began...\n");
			break;
		}
		move_numb++;
		printf("	You have %d foxes alive.\n", p_foxleft);
		printf("	AI have %d foxes alive.\n", a_foxleft);

		if (move_numb % 10 == 0)
		{
			for (i = 0; i < 10; i++)
				for (j = 0; j < 10; j++)
				{
					if (a[i][j] > 0) a[i][j] = 0;  // Let's try to clear AI working array sometimes, because after big number of turns algorithm works bad
				}
			beg_shots = 0;  // Start again from the beginning
		}
	}
	return 0;
}
