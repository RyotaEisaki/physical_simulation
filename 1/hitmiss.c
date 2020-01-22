#include<stdio.h>
#include<stdlib.h>
#include <math.h>

int main(void){
    FILE *fp ;
    
    // int size = 100;
    // int size = 1000;
    int size = 10000;
    
    int count=0;
    double x[size];
    double y[size];

    fp = fopen("misshit1.csv", "w"); if (fp == NULL) {
        fprintf(stderr, "Error!¥n");
        exit(1);
    }

    int seed[10] = {149,193,251,383,457,503,691,761,829,991};

    int loop=10;
    int loop_count;
    double area_sum;
    double area_ave;

    for (int loop_count =0;loop_count<loop;loop_count++){
        srand(seed[loop_count]);
        count=0;
        for (int i = 0; i < size; i++)
        {
            // x
            // 0~2　- 1→ -1~1
            double x_r = 1+(double)(2*rand()/(RAND_MAX + 1.0 ));
            double x_=x_r-1.0;         
            
            // y
            // 0~2　- 1→ -1~1
            double y_r = 1+(double)(2*rand()/(RAND_MAX + 1.0 ));
            double y_=y_r-1.0;

            if((y_>=-sqrt(1-x_*x_)) && (y_<=sqrt(1-x_*x_))){
                count++;
            }
        }
    // printf("%d\n",loop_count+1);
    // printf("%d\n",seed[loop_count]);
    // printf("%s%d\n","Hit: ", count);

    double area=((double)count/(double)size)*4;

    // printf("%s%lf\n","Area: ", area);
    // printf("\n");

    area_sum+=area;
    }
    printf("%s%d\n","Quantity: ", size);
    area_ave=area_sum/loop;
    printf("%s%lf\n","AVERAGE: ", area_ave);
    double value=(3.14159-area_ave)/3.14159;
    printf("%s%lf\n","Value: ", value);
    
    fclose(fp);
    return 0;
}