#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

//TEST CODE//
int sudoku[9][9];

void readPuzzle(FILE *file) {
	for (int i = 0; i<9; i++) {
			for (int j = 0; j<9; j++) {
				fscanf(file, "%d", &sudoku[i][j]);
			}
		}

}

int main() {

	FILE *puzzle = fopen("puzzle.txt", "r");
	readPuzzle(puzzle);

	printf("%d", sudoku[0][0]);
	printf("%d", sudoku[5][5]);
	return 0;
}
