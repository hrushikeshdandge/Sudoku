#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int sudoku[9][9];

typedef struct {
	int column,row;
} box_coordinates;

int correct[3] = { 0, 0, 0 };
void readPuzzle(FILE *file) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			fscanf(file, "%d", &sudoku[i][j]);
		}
	}

}

void *rowChecker() {
	int passfail = 1;
	for (int a = 0; a < 9; a++) { //goes through each row
		int flags[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
		for (int i = 0; i < 9; i++) { //goes through each col
			if (flags[sudoku[a][i] - 1] == 0) //goes through each value 1 - 9
				flags[sudoku[a][i] - 1] = 1;
			else {
				passfail = 0;
				break;
			}
		}
	}
	printf("Rowcheck pass(1)/fail(0): %d\n", passfail);
	return NULL;
}

void *columnChecker() {
	int incorrect = 0;
	for (int column = 0; column < 9; column++) {
		//Set array of flags
		int flag[9];
		for (int i = 0; i < 9; i++) {
			flag[i] = 0;
		}

		for (int row = 0; row < 9; row++) {
			int toCheck = sudoku[row][column];
			if (flag[toCheck - 1] == 0) {
				flag[toCheck - 1] = 1;
			} else {

				printf("Column incorrect; Row: %d Column: %d \n", row + 1,
						column + 1);
				incorrect = 1;
				break;
			}
			if (incorrect == 1)
				break;
		}
	}
	return NULL;
}

/*check the box that is sent into it.
	it used the box coordinates to offset the validator when checking the values
*/
void *check_box(void * boxInfo) {

	int value;
	box_coordinates *coordinates = boxInfo;
	int box_column = coordinates->column;
	int box_row = coordinates->row;

	int error = 0;
	
	//flags to check if the value was already seen in the box
	int flags[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	//go through all the elements in the box
	for (int column = 0; column < 3; column++) {
		for (int row = 0; row < 3; row++) {
			value = sudoku[row + box_row][column + box_column];
			//printf("Value= %d\n", value);

			//if the value has been found before, there is an error in the box
			if (flags[value - 1] == 1) {
				printf("ERROR IN ROW: %d COLUMN: %d\n", row + box_row + 1, column + box_column + 1);
				printf("Value: %d", value);
				error = 1;
				break;

			} else {
				flags[value - 1] = 1;
			}
		}
		if (error == 1) {
			break;
		}
	}
	//prints out the location of the box if it has an error	
	if (error == 1){
		printf("ERROR IN BOX: Column: %d, Row: %d\n", box_row,
			box_column);

	}else
		printf("Passed Box: Column: %d, Row: %d\n", box_row,
			box_column);

	return NULL;
}

int main() {

	FILE *puzzle = fopen("puzzle.txt", "r");
	readPuzzle(puzzle);

	pthread_t pth;
	pthread_create(&pth, 0, rowChecker, (void *) "Row Checker motherfuckers");

	pthread_t pth2;
	pthread_create(&pth2, 0, columnChecker, (void *) "Column");

	pthread_t boxThread[9];
	//start coordinates for the seprate boxes
	box_coordinates boxes[9];

	//makes threads for each box in sudoku by offsetting each box by the coordinates
	int i = 0;
	for (int countcolumn = 0; countcolumn <= 6; countcolumn += 3) {
		for (int countrow = 0; countrow <= 6; countrow += 3) {
			boxes[i].column = countcolumn;
			boxes[i].row = countrow;
			pthread_create(&boxThread[i], 0, check_box, (void *) &boxes[i]);
			i++;
		}
	}
	//////JOINS/////

	pthread_join(pth, 0);
	pthread_join(pth2, 0);
	for(int i = 0; i < 9; i++){
		pthread_join(boxThread[i], 0);
	}

	return 0;
}
