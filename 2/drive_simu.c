#include <stdio.h>
#include<stdlib.h>
#include <math.h>

int main(void) {
    int length =20;
   
    int state[length];
    double density;
    
    int time =20;
   
   double t;

    //first state
    scanf("%lf", &density);

    int seed[10] = {149,193,251,383,457,503,691,761,829,991};
    srand(seed[5]);

    for (int i=0;i<length;i++){
            t=(double)(1*rand()/(RAND_MAX + 1.0 ));
            printf("%lf\n",t);
            if (t<density){
                state[i]=1;
            }
            else{
                state[i]=0;
            }
    }

    printf("%s\n","Base State; ");
    int test;
    for (int k=0; k<length; k++){
        if(state[k]==1){
            test++;
        }
        printf("%d",state[k]);
    }
    printf("\n");
    // double value= (double)test/length;
    // printf("%f\n",value);
    

    // CA184
    for (int i=0; i<time; i++){
        for(int l=0; l<length;l++){
        state[length-1]=(i==0)
        }
        for (int k=0; k<length; k++){
            printf("%d",state[k]);
        }
        printf("\n");
    }

    return 0;
}
    

