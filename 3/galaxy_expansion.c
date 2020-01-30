#include<stdio.h>
#include<stdlib.h>
#include <math.h>

int main(void){
    FILE *fp ;
    int size = 500;

    double x0[size];
    double y0[size];

    fp = fopen("data.csv", "w"); if (fp == NULL) {
        fprintf(stderr, "Error!¥n");
        exit(1);
    }

    //乱数を生成
    int number;
    int seed[10] = {149,193,251,383,457,503,691,761,829,991};
    printf("%s\n","Please input the numbeer (1~10) to select seed;");
    printf("%s\n","1: 149, 2: 193, 3: 251, 4: 383, 5: 457, 6: 503, 7: 691, 8: 761, 9: 829, 10: 991");
    scanf("%d", &number);
    srand(seed[number-1]);

    fprintf(fp,"%s,%s,%s,%s\n","x","y","x_","y_");

    for (int i = 0; i < size; i++)
    {
        // 0~2　- 1→ -1~1
        double x_r1 = (double)(10.0*rand()/(RAND_MAX + 1.0 ));
        double x_r=x_r1-5.0;
        x0[i]=x_r;
        
        double randmax=sqrt(25-x_r*x_r);
        // double randmax_=randmax*10*10*10*10*10*10;
        double y_r1 = (double)(2*randmax*rand()/(RAND_MAX + 1.0 ));  
        // double y_r=(y_r1-randmax_)/(10*10*10*10*10*10);
        double y_r=y_r1-randmax;
        y0[i]=y_r;
        // printf("%lf,%lf\n",x0[i],y0[i]);
    }

    //シミュレーション
    double H=3.5;
    double org=50.0;
    double dt=0.1;
    int nk=20;

    double vx[size];
    double vy[size];
    //膨張前
    double x[size];
    double y[size];
    //膨張後
    double x_[size];
    double y_[size];

    //初速度を設定
    for (int i=0;i<size;i++){
        vx[i]=H*x0[i];
        vy[i]=H*y0[i];
    }

    //全天体の位置を移動
    for (int i=0;i<size;i++){
        x[i]=x0[i]+org;
        y[i]=y0[i]+org;
    }

    for (int i=0;i<size;i++){
        x_[i]=x[i];
        y_[i]=y[i];
    }

    //新しい位置を計算
    for (int l; l<nk;l++){
        for (int i;i<size;i++){
            double t1 =x_[i]+vx[i]*dt;
            double t2=y_[i]+vy[i]*dt;
            x_[i]=t1;
            y_[i]=t2;
        }
    }

     for (int i = 0; i < size; i++)
    {
        printf("%lf,%lf,%lf,%lf\n",x[i],y[i],x_[i],y_[i]);
    }


    for (int i=0;i<size;i++){
        fprintf(fp,"%lf,%lf,%lf,%lf\n",x[i],y[i],x_[i],y_[i]);
    }
    fclose(fp);
    return 0;
}