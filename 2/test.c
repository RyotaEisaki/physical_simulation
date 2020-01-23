#include <stdio.h>
#include<stdlib.h>
#include <math.h>

int main(void) {
    int length =10;
    int state[length];
    double density;
    int time =20;
    double t;
    double l;

    //first state
    scanf("%lf", &density);

    int seed=193;
    srand(seed);
    // t=(double)(2*rand()/(RAND_MAX + 1.0 ));
    // l=(double)(2*rand()/(RAND_MAX + 1.0 ));

    printf("%f\n",t);
    printf("%f\n",l);
    for (int i=0;i<length;i++){
            t=(double)(2*rand()/(RAND_MAX + 1.0 ));
            printf("%lf\n",t);
            if (t<density){
                state[i]=1;
            }
            else{
                state[i]=0;
            }
    }
    for (int k=0; k<length; k++){
        printf("%d",state[k]);
    }
    
    // // printf("%f\n",);
}