#include<stdio.h>
#include<stdlib.h>
#include <math.h>

int main(void){
  
    
    int size = 10000;
    
    int count=0;
   

  

    int seed[10] = {149,193,251,383,457,503,691,761,829,991};

    int loop=10;
    int loop_count;


    for (int loop_count =0;loop_count<loop;loop_count++){
        srand(seed[0]);
        printf("%d\n",rand());
    }
    return 0;
}
