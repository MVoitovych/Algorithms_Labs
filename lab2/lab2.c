#include <stdio.h>
#include <stdlib.h>

#define E INT_MAX


int **generateMatrix(int col, int row) {

    int **matrix = (int **) (malloc(sizeof(int *) * row));

    for (int r = 0; r < row; r++) {
        matrix[r] = (int *) malloc(sizeof(int) * col);
        for (int c = 0; c < col; c++) {
            int a = rand() % 5;
            if (a >= 3)
                matrix[r][c] = E;
            else matrix[r][c] = 0;

        }
    }
    return matrix;
}

void beautyPrint(int **matrix, int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            char c = matrix[i][j] == 0 ? '~' : '@';
            printf("%c", c);
        }
        printf("\n");
    }
}

void printMatrix(int **matrix, int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            printf("[%d]", matrix[i][j]);
        }
        printf("\n");
    }
}


void checkNeighbours(int **matrix, int row, int col, int max_row, int max_col, int num) {

    if (matrix[row][col] != E)
        return;

    matrix[row][col] = num;

    if (row != 0) checkNeighbours(matrix, row - 1, col, max_row, max_col, num);

    if (row != max_row) checkNeighbours(matrix, row + 1, col, max_row, max_col, num);

    if (col != 0) {
        if (row != 0) checkNeighbours(matrix, row - 1, col - 1, max_row, max_col, num);
        checkNeighbours(matrix, row, col - 1, max_row, max_col, num);
        if (row != max_row) checkNeighbours(matrix, row + 1, col - 1, max_row, max_col, num);
    }

    if (col < max_col) {
        if (row != 0) checkNeighbours(matrix, row - 1, col + 1, max_row, max_col, num);
        checkNeighbours(matrix, row, col + 1, max_row, max_col, num);
        if (row != max_row) checkNeighbours(matrix, row + 1, col + 1, max_row, max_col, num);

    }

}

void getIslands(int **matrix, int max_row, int max_col) {
    int num = 0;
    for (int row = 0; row < max_row; row++) {
        for (int col = 0; col < max_col; col++) {
            if (matrix[row][col] == E) {
                num++;
                checkNeighbours(matrix, row, col, max_row - 1, max_col - 1, num);
            }
        }
    }
}


void run() {

    const int max_row = 10;
    const int max_col = 10;
    int **matrix = generateMatrix(max_row, max_col);

    beautyPrint(matrix, max_row, max_col);
    getIslands(matrix, max_row, max_col);


    printf("===============================\n");
    printMatrix(matrix, max_row, max_col);
}


int main() {
    run();
}


