#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

int main(int argc, char *argv[])
{
    FILE *fo;
    char *fname;
    fname=”data.csv”;
    if( (fo=fopen(fname,"w")) == NULL ){
    printf("File[%s] dose not open!! ¥n",fname);
    exit(0);
    }
    for(i=1; i<=n; i++) fprintf(fo, "%f,%f¥n", x[i],y[i]);
}