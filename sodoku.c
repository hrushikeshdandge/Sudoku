#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int sudoku[9][9];
int correct[3] = {0, 0, 0};
void readPuzzle(FILE *file) {
	for (int i = 0; i<9; i++) {
			for (int j = 0; j<9; j++) {
				fscanf(file, "%d", &sudoku[i][j]);
			}
		}

}

/*
void *rowChecker() {
	for (int i = 0; i < 9; i++) {
		if ([i] != [i + 1]) {

		}
	}
}
*/
void *columnChecker() {
	int incorrect = 0;
	for (int column = 0; column < 9; column++) {
		//Set array of flags
		int flag[9];
		for (int i = 0; i < 9; i++){
			flag[i] = 0;
		}

		for (int row = 0; row < 9; row ++) {
			int toCheck = sudoku[row][column];
			if (flag[toCheck -1] == 0) {
				flag[toCheck -1] = 1;
			} else {

				printf("Column incorrect; Row: %d Column: %d \n", row+1, column+1);
				incorrect = 1;
				break;
			}
		if (incorrect == 1)
			break;

		}
	}
	if (incorrect != 1) {
		printf("Columns are all correct!\n"); }
		correct[0] = 1;
	return NULL;

}

void *check_box(){
	//define first check
	//int row = 0;
	//int column = 0;
	for(int count = 0; count < 9; count++){
		for(int i = 0; i < 3; i++){
			
		}
	}
}


int main() {


	FILE *puzzle = fopen("puzzle.txt", "r");
	readPuzzle(puzzle);

	pthread_t pth2;
	pthread_create(&pth2, 0, columnChecker, (void *) "Column");

	pthread_join(pth2, 0);





	/* Print tests for puzzle
	printf("%d", sudoku[0][0]);
	printf("%d", sudoku[5][5]);
	*/
	return 0;
}
