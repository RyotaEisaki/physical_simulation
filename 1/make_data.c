#include<stdio.h>
#include<stdlib.h>
#include <math.h>

int main(void){
    FILE *fp ;
    int size = 500;
    double x[size];
    double y[size];

    fp = fopen("data.csv", "w"); if (fp == NULL) {
        fprintf(stderr, "Error!¥n");
        exit(1);
    }

    int seed=193;
    srand(seed);

    fprintf(fp,"%s,%s\n","x","y");

    for (int i = 0; i < size; i++)
    {
        // 0~2　- 1→ -1~1
        double x_r1 = 1+(double)(2*rand()/(RAND_MAX + 1.0 ));
        double x_r=x_r1-1.0;
        x[i]=x_r;
        
        double randmax=sqrt(1-x_r*x_r);
        double randmax_=randmax*10*10*10*10*10*10;
        double y_r1 = 1+(double)(2*randmax_*rand()/(RAND_MAX + 1.0 ));  
        double y_r=(y_r1-randmax_)/(10*10*10*10*10*10);
        y[i]=y_r;


        printf("%lf,%lf\n",x[i],y[i]);
        fprintf(fp,"%lf,%lf\n",x[i],y[i]);
    }
    fclose(fp);
    return 0;
}