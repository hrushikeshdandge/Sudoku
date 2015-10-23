#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int sudoku[9][9];

void readPuzzle(FILE *file) {
	for (int i = 0; i<9; i++) {
			for (int j = 0; j<9; j++) {
				fscanf(file, "%d", &sudoku[i][j]);
			}
		}

}

void *rowChecker() {
	for (int i = 0; i < 9; i++) {
		if ([i] != [i + 1]) {

		}
	}
}


void *check_box(){
	//define first check
	int row = 0;
	int column = 0;
	for(int count = 0; i < 9; i++){
		for(int i = 0; i < 3; i++){
			
		}
	}
}


int main() {


	printf("casual is working");
	pthread_t pth;
	pthread_create(&pth, 0, rowChecker, (void *) "Thread 1");

	pthread_join(pth, 0);


	FILE *puzzle = fopen("puzzle.txt", "r");
	readPuzzle(puzzle);


	printf("%d", sudoku[0][0]);
	printf("%d", sudoku[5][5]);
	return 0;
}
