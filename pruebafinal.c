#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void guardar (double data[10][1000], int col, double matriz[10][8]);
void imprimeM(char s[],double data[10][1000],double data1[10][1000],double data2[10][1000],float* a);
void imprimeV(double data[10][1000]);
void cini(double vx[10][1000], double vy[10][1000], double vz[10][1000], double x[10][1000],  double y[10][1000],  double z[10][1000], double m[10][1000]);
void gene(double vx[10][1000], double vy[10][1000], double vz[10][1000], double x[10][1000],  double y[10][1000],  double z[10][1000], double m[10][1000], int tiempo);
double radio(double x[10][1000],  double y[10][1000],  double z[10][1000], int tiempo, int c, int c1);
double ace(int pos, int tiempo, int p, double m[10][1000],double x[10][1000],  double y[10][1000],  double z[10][1000]);
int main(void){
    double dt=0.0001;
    float t[1000];
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

  
	double x[10][1000];
    double y[10][1000];
    double z[10][1000];
    double vx[10][1000];
    double vy[10][1000];
    double vz[10][1000];
    double m[10][1000];
	guardar(m,1,matrix);
    guardar(x,2,matrix);
    guardar(y,3,matrix);
    guardar(z,4,matrix);
    guardar(vx,5,matrix);
    guardar(vy,2,matrix);
    guardar(vz,2,matrix);
    cini(vx,vy,vz,x,y,z,m);
    
	
    for (i=2;i<1000;i++){
      t[0]=0.0;
      t[1]=t[0]+dt;
      t[i]=t[i-1]+dt;
      gene(vx,vy,vz,x,y,z,m,i);
        
    }
    imprimeM("datos.txt",x,y,z,t);
     
}
void guardar (double data[10][1000], int col, double matriz[10][8]){
    int i=0;

    for (i=0;i<10;i++){
        data[i][0] = matriz[i][col];
    }
}
//IMPRIME SERIE DE DATOS,POSX,POSY,POSZ,T
void imprimeM(char s[],double data[10][1000],double data1[10][1000],double data2[10][1000],float* a){
  FILE *arch =fopen(s,"w+");
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 1000; j++) {
      printf("%f,%f,%f,%f\n",data[i][j],data1[i][j],data2[i][j],a[i]);
       
    }
     
  }
     
}
void imprimeV(double data[10][1000]){
  for (int i = 0; i < 10; i++) {
    printf("X[%d][0] es: %f\n",i,data[i][0]);
  }
}




void cini(double vx[10][1000], double vy[10][1000], double vz[10][1000], double x[10][1000],  double y[10][1000],  double z[10][1000], double m[10][1000]){
    int i=0;
    double dt=0.01;
    for (i=0;i<10;i++){
        x[i][1]=x[i][0]+dt*vx[i][0];
        y[i][1]=y[i][0]+dt*vy[i][0];
        z[i][1]=z[i][0]+dt*vz[i][0];
        vx[i][1]=vx[i][0]+dt*ace(1,0,i,m,x,y,z);
        vy[i][1]=vy[i][0]+dt*ace(2,0,i,m,x,y,z);
        vz[i][1]=vz[i][0]+dt*ace(3,0,i,m,x,y,z);  
        
    }   
}
void gene(double vx[10][1000], double vy[10][1000], double vz[10][1000], double x[10][1000],  double y[10][1000],  double z[10][1000], double m[10][1000], int tiempo){
    double dt=0.1;
    int i=0;
    for (i=0;i<10;i++){
        x[i][tiempo]=x[i][tiempo-2]+2*dt*vx[i][tiempo-1];
        y[i][tiempo]=y[i][tiempo-2]+2*dt*vy[i][tiempo-1];
        z[i][tiempo]=z[i][tiempo-2]+2*dt*vz[i][tiempo-1];
        vx[i][tiempo]=vx[i][tiempo-2]+2*dt*ace(1,tiempo-1,i,m,x,y,z);
        vy[i][tiempo]=vy[i][tiempo-2]+2*dt*ace(2,tiempo-1,i,m,x,y,z);
        vz[i][tiempo]=vz[i][tiempo-2]+2*dt*ace(3,tiempo-1,i,m,x,y,z);  
        
    }   
    
    
}
double radio(double x[10][1000],  double y[10][1000],  double z[10][1000], int tiempo, int c, int c1){
    double radio=0;
    radio=sqrt((x[c][tiempo]-x[c1][tiempo])*(x[c][tiempo]-x[c1][tiempo])+(y[c][tiempo]-y[c1][tiempo])*(y[c][tiempo]-y[c1][tiempo])+(z[c][tiempo]-z[c1][tiempo])*(z[c][tiempo]-z[c1][tiempo]));
    return radio;
}
double ace(int pos, int tiempo, int p, double m[10][1000],double x[10][1000],  double y[10][1000],  double z[10][1000]){
    double a=0;
    double G = 1.985229E-29;
    int i=0;
    for (i=0;i<10;i++){
        if (p!=i){
            if (pos==1){
                a+=G*m[i][0]*(x[p][tiempo]-x[i][tiempo])/pow(radio(x,y,z,tiempo,p,i),3);
            
            }
            if (pos==1){
                a+=G*m[i][0]*(y[p][tiempo]-y[i][tiempo])/pow(radio(x,y,z,tiempo,p,i),3);
            
            }
            if (pos==1){
                a+=G*m[i][0]*(z[p][tiempo]-z[i][tiempo])/pow(radio(x,y,z,tiempo,p,i),3);
            
            }
       
    
        }
    }
    return a;
}

