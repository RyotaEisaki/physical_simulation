#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int nm = 99; //一軸あたりの格子点数
const int G=1;
const double M=1;
const int ni=50;
const double dt=0.1;
const double org=50;
const int  dx=1;
const int  dy=1;

const double H=3.5;
const int size=500;
const int seed=383;

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
int check(double, double);
void calc_ro ();
void init_phi();
void gauss_seidel();

void gravity_field ();
void calc_move ();
void calc_power ();
int ngp (double);
void calc_velocity ();
void calc_position ();
void move ();
void print_move ();

int check (double x, double y) {
    if ((x * x + y * y) > 25.0) return 0;
    else { return 1;}
}

void init_place () {
  double x_, y_;
  srand(seed);
  for (int t = 0; t < size; ++t) {
    x_ = -5.0 + (double) (10.0 * rand()/RAND_MAX);
    y_ = -5.0 + (double) (10.0 * rand()/RAND_MAX);
    while (0 == check (x_, y_)) {
      x_ = -5.0 + (double) (10.0 * rand()/RAND_MAX);
      y_ = -5.0 + (double) (10.0 * rand()/RAND_MAX);
    }
    x[t] = x_;
    y[t] = y_;
  }
}

void init_phi () {
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      phi[i][j] = 0;
    }
  }
}

void calc_ro () {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      ro[i][j] = 0.0;
    }
  }
  for (int i = 0; i < size; i++) {
    ro[(int)floor(x[i] + 0.5)][(int)floor(y[i] + 0.5)] += M;
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

void gravity_field () {
  for (int ix = 0; ix < size; ix++) {
    for (int iy = 0; iy < size; iy++) {
      Fx[ix][iy] = ( - ((phi[ix+1][iy]) - (phi[ix][iy]))) / dx;
      Fy[ix][iy] = ( - ((phi[ix][iy+1]) - (phi[ix][iy]))) / dx;
    }
  }
}

int ngp (double p) {
  return (int) floor(p + 0.5);
}

void calc_power () {
  int _x, _y;
  for (int i = 0; i < size; i++) {
    _x = ngp (x[i]);
    _y = ngp (y[i]);
    Fpx[i] = M * Fx[_x][_y];
    Fpy[i] = M * Fy[_x][_y];
  }
}

void calc_velocity () {
  for (int ip = 0; ip < size; ip++) {
    vx[ip] = vx[ip] + (Fpx[ip] / M) * dt;
    vy[ip] = vy[ip] + (Fpy[ip] / M) * dt;
  }
}

void calc_position () {
  for (int i = 0; i < size; i++) {
    x[i] += vx[i] * dt;
    y[i] += vy[i] * dt;
  }
}

void calc_move () {
  calc_power ();
  calc_velocity ();
  calc_position ();
}

void move () {
  calc_ro ();
  gauss_seidel ();
  gravity_field ();
  calc_move ();
}

void print_position () {
  printf ("\n");
  for (int t = 0; t < size; t++) {
    printf ("%f,%f\n", x[t], y[t]);
  }
}

int main (void) {

    FILE *fp ;

    fp = fopen("data.csv", "w"); if (fp == NULL) {
        fprintf(stderr, "Error!¥n");
        exit(1);
    }

    //時間ステップの指定
    int step;
    printf("%s\n","Please select the number; 0 or 20 or 40");
    scanf("%d", &step);
    int nk=step;


    init_place ();

  for (int ip = 0; ip < size; ip++) {
    vx[ip] = H * x[ip];
    vy[ip] = H * y[ip];

    x[ip] = x[ip] + org;
    y[ip] = y[ip] + org;
  }

//   print_position ();
  init_phi ();

//   for (int i = 0; i < nk; i++) {
//     move ();
//   }
//   print_position ();
  for (int i = 0; i < nk; i++) {
    move ();
  }
  print_position ();
  for (int i=0;i<size;i++){
        fprintf(fp,"%lf,%lf\n",x[i],y[i]);
    }
  return 0;
}
