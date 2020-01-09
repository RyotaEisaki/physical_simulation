#include<stdio.h>
#include<stdlib.h>
#include <math.h>

int main(void){
    FILE *fp ;
    int size = 500;
    int count=0;
    double x[size];
    double y[size];

    fp = fopen("misshit1.csv", "w"); if (fp == NULL) {
        fprintf(stderr, "Error!¥n");
        exit(1);
    }

    int seed=193;
    srand(seed);
    fprintf(fp,"%s,%s\n","x","y");
    for (int i = 0; i < size; i++)
    {
        // 0~2　- 1→ -1~1
        double x_r = 1+(double)(2*rand()/(RAND_MAX + 1.0 ));
        double x_=x_r-1.0;
        x[i]=x_;
        
        // 0~2　- 1→ -1~1
        double y_r = 1+(double)(2*rand()/(RAND_MAX + 1.0 ));
        double y_=y_r-1.0;
        y[i]=y_;

        // printf("%lf,%lf\n",x[i],y[i]);
        // fprintf(fp,"%lf,%lf\n",x[i],y[i]);
         
        if((y_>=-sqrt(1-x_*x_)) && (y_<=sqrt(1-x_*x_))){
            count++;
        }
    }
    printf("%s,%d\n","Hit: ",count);
    double area=(double)count/(double)size*4;
    printf("%s,%lf\n","Area: ", area);
    double value=(3.14159-area)/3.14159;
    printf("%s,%lf\n","Value: ", value);
    fclose(fp);
    return 0;
}