#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void guardar (double data[10][1000], int col, double matriz[10][8]);
void imprimeM(double data[10][8]);
void imprimeV(double data[10][1000]);

int main(void){
	FILE *datos;
	datos=fopen("coordinates.csv","r");
	int len=300;
	char ap[len];
	char *ep;
	const char *delimiter;
	delimiter= ",";
	double matrix[10][8];
	int i=0, j=0;
  while(fgets(ap,len,datos)){
		j=0;
		//printf("LINE IS:%s", line_buffer );
		ep = strtok(ap,delimiter);
    while(ep != NULL){
    	if(j!=0){
      	matrix[i][j-1] = atof(ep);
        //printf("ITEM IN LINE: %s",split_buffer);
        ep= strtok(NULL,delimiter);
      }
			j+=1;
    }
    i+=1;
  }

  imprimeM(matrix);
	double x[10][1000];
	guardar(x,2,matrix);
	imprimeV(x);
}
void guardar (double data[10][1000], int col, double matriz[10][8]){
    int i=0;

    for (i=0;i<10;i++){
        data[i][0] = matriz[i][col];
    }
}
void imprimeM(double data[10][8]){
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 8; j++) {
      printf("Datos[%d][%d] es: %f\n",i,j,data[i][j]);
    }

  }
}
void imprimeV(double data[10][1000]){
  for (int i = 0; i < 10; i++) {
    printf("X[%d][0] es: %f\n",i,data[i][0]);
  }
}
