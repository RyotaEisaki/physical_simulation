#include<stdio.h>
#include<stdlib.h>
#include <math.h>

int ro_calc(int x, int y){
    return 6*x-3*y;
}

int main(void){
    int ix,iy;   
    int nm=2; /* nm：1軸当たりの格子点数*/
    
    int ni; /* ni：反復回数*/
    
    int G=1;
    int dx=1;
    int ro[4][4]; //密度
    double phi[4][4]; //求める解φ
    double p1,p2;

    printf("%s\n","Please input the number of times;");
    scanf("%d", &ni);


    //初期化
    for(ix=0; ix<=4; ix++) for(iy=0; iy<=4; iy++) {
            phi[ix][iy] = 0.0;
        }

    phi[1][3]=22.5;
    phi[2][3]=36;
    phi[3][1]=-4.5;
    phi[3][2]=9;

    for(ix=0; ix<=4; ix++){ 
        for(iy=0; iy<=4; iy++) {
            ro[ix][iy] = ro_calc(ix, iy);
        }
    }

    //gauss_seidel
    for(int i=1; i<=ni; i++){   
        for(ix=1; ix<=nm; ix++) for(iy=1; iy<=nm; iy++){
            p1 = phi[ix+1][iy]+phi[ix-1][iy]+phi[ix][iy+1]+phi[ix][iy-1];
            p2 = G*ro[ix][iy]*dx*dx; /* G：定数*/
            phi[ix][iy] = p1/4 - p2/4;
        }
    }

    printf("%s%d\n","Loop: ",ni);
    for (int iy = 3; iy > -1; iy--) {
        for (int ix = 0; ix < 4; ix++) {
            printf("%f ",phi[ix][iy]);
    }
    printf("\n");
    }

    return 0;   
}