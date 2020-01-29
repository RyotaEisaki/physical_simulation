// CA.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int cell[20];
    int tmp[20];
    int i, j, t;
    double dens = 0.7;

    srand(149);
    for (i = 0; i < 20; i++) {
        cell[i] = ((double)rand() / (double)RAND_MAX) < dens ? 1 : 0;
    }
    printf("t = 0 :  ");
    for (j = 0; j < 20; j++) {
        printf("%d ", cell[j]);
    }
    printf("\n");

    t = 1;
    while (t <= 20) {
        for (j = 0; j < 20; j++) {
            if ((j-1 < 0 ? cell[19] : cell[j-1]) == 1 && cell[j] == 0) {
                tmp[j] = 1;
                continue;
            }
            if (cell[j] == 1 && (j+1 < 20 ? cell[j+1] : cell[0]) == 1) {
                tmp[j] = 1;
                continue;
            }
            tmp[j] = 0;
        }
        memcpy(cell, tmp, sizeof(tmp));

        if (t < 10) {
            printf("t = %d :  ", t);
        } else {
            printf("t = %d:  ", t);
        }
        for (j = 0; j < 20; j++) {
            printf("%d ", cell[j]);
        }
        printf("\n");
        t++;
    }
}