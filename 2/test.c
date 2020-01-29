#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include <string.h>

int main(void) {
    int length =20;
    int state[length];
    int tmp[length];
    double density;
    int number;
    
    int time =20;
   
    double random;

    //first state
    printf("%s\n","Please input the number (0~1) to decide the initial density;");
    scanf("%lf", &density);

    int seed[10] = {149,193,251,383,457,503,691,761,829,991};
    printf("%s\n","Please input the numbeer (1~10) to select seed;");
    printf("%s\n","1: 149, 2: 193, 3: 251, 4: 383, 5: 457, 6: 503, 7: 691, 8: 761, 9: 829, 10: 991");
    scanf("%d", &number);
    srand(seed[number-1]);

    printf("\n");
    printf("%s\n","CONDITION;");
    printf("%s%lf\n","- Density; ",density);
    printf("%s%d\n","- Seed; ",seed[number-1]);
    printf("\n");
    printf("%s\n","SIMULATION RESULT;");

    for (int i=0;i<length;i++){
            random=(double)(1*rand()/(RAND_MAX + 1.0 ));
            // printf("%lf\n",random);
            if (random<density){
                state[i]=1;
            }
            else{
                state[i]=0;
            }
    }

    printf("%s","t = 0 :  ");
    // int test;
    for (int k=0; k<length; k++){
        if(state[k]==1){
            // test++;
        }
        printf("%d ",state[k]);
    }
    printf("\n");
    // double value= (double)test/length;
    // printf("%f\n",value);
    

    int t = 1;
    while (t <= length) {
        for (int j = 0; j < length; j++) {
            if ((j-1 < 0 ? state[length-1] : state[j-1]) == 1 && state[j] == 0) {
                tmp[j] = 1;
                continue;
            }
            if (state[j] == 1 && (j+1 < length ? state[j+1] : state[0]) == 1) {
                tmp[j] = 1;
                continue;
            }
            tmp[j] = 0;
        }
        memcpy(state, tmp, sizeof(tmp));

        if (t < 10) {
            printf("t = %d :  ", t);
        } else {
            printf("t = %d:  ", t);
        }
        for (int j = 0; j < length; j++) {
            printf("%d ", state[j]);
        }
        printf("\n");
        t++;
    }
}