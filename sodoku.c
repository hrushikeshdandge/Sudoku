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
	return NULL;


}

void *check_box(){


	int value;
	int error = 0;
	for(int countcolumn = 0; countcolumn <= 6; countcolumn+=3){
		for(int countrow = 0; countrow <= 6; countrow+=3){
			int flags[9] = {0,0,0,0,0,0,0,0,0};
			for(int column = 0; column < 3; column++){
				for(int row = 0; row < 3; row++){
					value = sudoku[row + countrow][column + countcolumn];
					printf("Value= %d\n",value);
					if(flags[value - 1] == 1){
						printf("ERROR IN ROW: %d COLUMN: %d\n",row + countrow + 1,column + countcolumn +1);
						//printf("Value: %d", value);
						int error = 1;
						break;

					}
					else{
						flags[value - 1] = 1;
					}
				}
				if(error == 1){
					break;
				}
			}
			if(error==1)
				printf("ERROR IN BOX: Column: %d, Row: %d",countcolumn,countrow);

		}


	}
}


int main() {



	FILE *puzzle = fopen("puzzle.txt", "r");
	readPuzzle(puzzle);

	pthread_t pth2;
	pthread_create(&pth2, 0, columnChecker, (void *) "Column");
	//pthread_t pth;
	pthread_t boxThread;
	//pthread_create(&pth, 0, rowChecker, (void *) "Thread 1");
	pthread_create(&boxThread,0,check_box,(void *)"Box checker");
	pthread_join(boxThread,0);
	//pthread_join(pth, 0);

	pthread_join(pth2, 0);




	


	



	/* Print tests for puzzle
	printf("%d", sudoku[0][0]);
	printf("%d", sudoku[5][5]);
	*/
	return 0;
}
