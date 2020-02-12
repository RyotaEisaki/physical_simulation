#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int nm = 99; //一軸あたりの格子点数
const int G=1;
const double M=1;
const double H=3.5;
const int ni=50;
const double dt=0.1;
const int size=500;
const double org=50;
const int  dx=1;


double x[size];
double y[size];

//速度
double vx[size];
double vy[size];

//ポテンシャル
double phi[size][size]; //求める解φ
//密度
int ro[size][size]; //密度

//重力場F
double Fx[size][size];
double Fy[size][size];

//天体が受ける力
double Fpx[size];
double Fpy[size];

//関数一覧
void init_phi();
void gauss_seidel ();
int nearest_value(double x);
void calc_ro ();
void gauss_seodel ();
void gravity_field ();

// void calc_move ();
// void calc_power ();
// void calc_velocity ();
// void calc_position ();
// void move_b ();

//ポテンシャルの初期化
void init_phi(){
    //初期化
    for(int ix=0; ix<=size; ix++) for(int iy=0; iy<=size; iy++) {
            phi[ix][iy] = 0.0;
    }
}

//NGP法
int nearest_value(double x) {
    return (int) floor(x + 0.5);
}

//密度の計算
void calc_ro () {
  for (int i = 0; i < size; i++) for (int j = 0; j < size; j++) {
      ro[i][j] = 0.0;
  }
  for (int i = 0; i < size; i++) {
    ro[nearest_value(x[i])][nearest_value(y[i])] += M;
  }
}

//ガウス・ザイデル法
void gauss_seidel(){
    double p1,p2;
    for(int i=1; i<=ni; i++){   
        for(int ix=1; ix<=nm; ix++) for(int iy=1; iy<=nm; iy++){
            p1 = phi[ix+1][iy]+phi[ix-1][iy]+phi[ix][iy+1]+phi[ix][iy-1];
            p2 = G*ro[ix][iy]*dx*dx; /* G：定数*/
            phi[ix][iy] = p1/4 - p2/4;
        }
    }
}

void gravity_field() {
  for (int ix = 0; ix < size; ix++) {
    for (int iy = 0; iy < size; iy++) {
      Fx[ix][iy] = ( - ((phi[ix + 1][iy]) - (phi[ix][iy]))) / dx;
      Fy[ix][iy] = ( - ((phi[ix][iy + 1]) - (phi[ix][iy]))) / dt;
    }
  }
}

// void move_a () {
//   for (int ip = 0; ip < 500; ++ip) {
//     X [ip] = X [ip] + vx[ip] * delta_t;
//     Y [ip] = Y [ip] + vy[ip] * delta_t;
//   }
// }



// void calc_power_field () {
//   for (int ix = 0; ix < 500; ++ix) {
//     for (int iy = 0; iy < 500; ++iy) {
//       Fx[ix][iy] = ( - ((phi[ix + 1][iy]) - (phi[ix][iy]))) / delta_x;
//       Fy[ix][iy] = ( - ((phi[ix][iy + 1]) - (phi[ix][iy]))) / delta_y;
//     }
//   }
// }


// void calc_power () {
//   int x, y;
//   for (int i = 0; i < 500; i++) {
//     x = find_point (X [i]);
//     y = find_point (Y [i]);
//     Fpx [i] = M * Fx [x] [y];
//     Fpy [i] = M * Fy [x] [y];
//   }
// }

// void calc_velocity () {
//   for (int ip = 0; ip < 500; ip++) {
//     vx [ip] = vx [ip] + (Fpx [ip] / M) * delta_t;
//     vy [ip] = vy [ip] + (Fpy [ip] / M) * delta_t;
//   }
// }

// void calc_position () {
//   for (int i = 0; i < 500; ++i) {
//     X[i] += vx[i] * delta_t;
//     Y[i] += vy[i] * delta_t;
//   }
// }

// void calc_move () {
//   calc_power ();
//   calc_velocity ();
//   calc_position ();
// }

// void move_b () {
//   calc_rho ();
//   calc_phi ();
//   calc_power_field ();
//   calc_move ();
// }

// void print_move () {
//   printf ("\n");
//   for (int t = 0; t < 500; ++t) {
//     printf ("%f,%f\n", X [t], Y [t]);
//   }
// }

int main(void){
    FILE *fp ;

    int size = 100;

    double x0[size];
    double y0[size];

    fp = fopen("data.csv", "w"); if (fp == NULL) {
        fprintf(stderr, "Error!¥n");
        exit(1);
    }

    //時間ステップの指定
    int step;
    printf("%s\n","Please select the number; 0 or 20 or 40");
    scanf("%d", &step);
    int nk=step;

    //乱数を生成
    int number;
    int seed[10] = {149,193,251,383,457,503,691,761,829,991};
    printf("%s\n","Please input the numbeer (1~10) to select seed;");
    printf("%s\n","1: 149, 2: 193, 3: 251, 4: 383, 5: 457, 6: 503, 7: 691, 8: 761, 9: 829, 10: 991");
    scanf("%d", &number);
    srand(seed[number-1]);

    fprintf(fp,"%s,%s,%s,%s\n","x_","y_","x","y");

  //初期座標
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

    //膨張前
    // double x_[size];
    // double y_[size];

    //膨張後
    // double x[size];
    // double y[size];

   //初速度を設定
    for (int i=0;i<size;i++){
        vx[i]=H*x0[i];
        vy[i]=H*y0[i];
    }

    //全天体の位置を第一象限へ移動
    for (int i=0;i<size;i++){
        x[i]=x0[i]+org;
        y[i]=y0[i]+org;
    }
  


  for (int s = 0; s < nk; s++) {
      calc_ro ();
      calc_phi ();
      gravity_field ();
      for (int i=0;i<size;i++){
            //天体が受ける力Fpを計算
            int nx=nearest_value(x[i]);
            int ny=nearest_value(y[i]);
            Fpx[i]=M*Fx[nx][ny];
            Fpy[i]=M*Fy[nx][ny];
            //天体の新しい速度を計算
            vx[i]=vx[i]+(Fpx[i]/M)*dt;
            vy[i]=vy[i]+(Fpx[i]/M)*dt;
            //天体の新しい位置を計算
            x[i]=x[i]+vx[i]*dt;
            y[i]=y[i]+vy[i]*dt;
        }
    }

    print_move ();
    for (int i = 0; i < 20; ++i) {
      move_b ();
    }
  print_move ();
  return 0;
}