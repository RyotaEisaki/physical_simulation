#include<stdio.h>
#include<stdlib.h>
#include <math.h>

const int nm=99; /* nm：1軸当たりの格子点数*/
const int G=1;
const double M=1;
const double H=3.5;
const int ni=50;
const double dt=0.1;
const int size=500;

const double Fp;


//初期座標
double x0[size]; 
double y0[size];


//座標
double x[size];
double y[size];

//速度
double vx[size];
double vy[size];


void init_v () {
  for (int i = 0; i < size; ++i) {
    vx[i] = H*x[i];
    vy[i] = H*y[i];
  }
}

void new_v(double Fp) {
    for (int ip = 0; ip < size; ++ip) {
        vx[ip] = vx[ip]+(Fpx/M)*dt;
        vy[ip] = vy[ip]+(Fpx/M)*dt;

  }
}

int ro_calc(int x, int y){
    return 6*x-3*y;
}

double gauss_seidel(int nm){
    int ix,iy;   
    int dx=1;
    int ro[nm+1][nm+1]; //密度
    double phi[nm+1][nm+1]; //求める解φ
    double p1,p2;

    //初期化
    for(ix=0; ix<=nm+1; ix++) for(iy=0; iy<=nm+1; iy++) {
            phi[ix][iy] = 0.0;
        }
    
    for(int i=1; i<=ni; i++){   
        for(ix=1; ix<=nm; ix++) for(iy=1; iy<=nm; iy++){
            p1 = phi[ix+1][iy]+phi[ix-1][iy]+phi[ix][iy+1]+phi[ix][iy-1];
            p2 = G*ro[ix][iy]*dx*dx; /* G：定数*/
            phi[ix][iy] = p1/4 - p2/4;
        }
    }

}


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

    fprintf(fp,"%s,%s,%s,%s\n","x_","y_","x","y");

    for (int i = 0; i < size; i++)
    {
        double x_r1 = (double)(10.0*rand()/(RAND_MAX + 1.0 ));
        double x_r=x_r1-5.0;
        x0[i]=x_r;
        
        double randmax=sqrt(25-x_r*x_r);
        double y_r1 = (double)(2*randmax*rand()/(RAND_MAX + 1.0 ));  
        double y_r=y_r1-randmax;
        y0[i]=y_r;
    }

    //シミュレーション
    double H=3.5;
    double org=50.0;
    double dt=0.1;
    int nk=20;

    double vx[size];
    double vy[size];

    //膨張前
    double x_[size];
    double y_[size];

    //膨張後
    double x[size];
    double y[size];


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

    for (int i = 0; i < size; i++)
    {
        printf("%lf%lf\n",x_[i],y_[i]);
    }

    //新しい位置を計算
    for (int l; l<nk;l++){
        for (int i=0;i<size;i++){
            x[i]=x[i]+vx[i]*dt;
            y[i]=y[i]+vy[i]*dt;
        }
    }
    
    for (int i = 0; i < size; i++)
    {
        printf("%lf%lf\n",x[i],y[i]);
    }

    for (int i = 0; i < size; i++)
    {
        printf("%lf,%lf,%lf,%lf\n",x_[i],y_[i],x[i],y[i]);
    }

    for (int i=0;i<size;i++){
        fprintf(fp,"%lf,%lf,%lf,%lf\n",x_[i],y_[i],x[i],y[i]);
    }
    fclose(fp);
    return 0;
}