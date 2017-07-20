#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void guardar (float *data, int col, double matriz[10][8]);
void cini(float* vx, float* vy, float* vz, float* x,  float* y,  float* z, float* masas);
void gene(float* vx, float* vy, float* vz, float* x,  float* y,  float* z, float* masas, int tiempo);
double radio(float* x,  float* y,  float* z, int tiempo, int c, int c1);
double ace(int pos, int tiempo, int p, float* masas,float* x,  float* y,  float* z);
int main(void){
    double dt= 0.01;
    int tmax= 20;
    float tiemp[tmax];
    int i=0, j=0;
    int size=tmax*8*10;
//Guardar espacio de memoria para matrix
    
    FILE *datos;
    datos=fopen("coordinates.csv","r");
    int len=300;
    char ap[len];
    char *ep;
    const char *delimiter;
    delimiter= ",";
    double matrix[10][8];
    while(fgets(ap,len,datos))
    {   j=0;
        //printf("LINE IS:%s", line_buffer );
        ep = strtok(ap,delimiter);
        while(ep != NULL)
        {
            
            if(j!=0){
                matrix[i][j-1] = atof(ep);
                //printf("ITEM IN LINE: %s",split_buffer);
                ep= strtok(NULL,delimiter);
            }
            j+=1;
        }
        
        i+=1;
    }
    
    
    //printf("%f\n", Matriz[1][1]);
    
//double masa=Matriz[0][1];

    
    int n=2000;
    float *masas=malloc((10)*sizeof(double));
    float *x=malloc((10*n)*sizeof(double));
    float *y=malloc((10*n)*sizeof(double));
    float *z=malloc((10*n)*sizeof(double));
    
    float *vx=malloc((10*n)*sizeof(double));
    float *vy=malloc((10*n)*sizeof(double));
    float *vz=malloc((10*n)*sizeof(double));
    
    float *ax=malloc(n*sizeof(double));
    float *ay=malloc(n*sizeof(double));
    float *az=malloc(n*sizeof(double));
    
    guardar(masas, 1, matrix);
    guardar(x,2,matrix);
    guardar(y,3,matrix);
    guardar(z,4,matrix);
    guardar(vx,5,matrix);
    guardar(vy,6,matrix);
    guardar(vz,7,matrix);
    //printf("%e\n", masas[2]);
    printf("%e\n", x[0]);
    
    tiemp[0]=0.0;
    tiemp[1]=tiemp[0]+dt;
    cini(vx,vy,vz,x,y,z,masas);
    return 0;
    
    
}

void guardar (float *data, int col, double matriz[10][8]){
    int i=0;

    for (i=0;i<10;i++){
        data[i]=matriz[i][col];
    }
}
void cini(float* vx, float* vy, float* vz, float* x,  float* y,  float* z, float* masas, double dt){
    int i=0;
    for (i=0;i<10;i++){
        x[i][1]=x[i][0]+dt*vx[i][0];
        y[i][1]=y[i][0]+dt*vy[i][0];
        z[i][1]=z[i][0]+dt*vz[i][0];
        vx[i][1]=vx[i][0]+dt*ace(1,0,i,masas,x,y,z);
        vy[i][1]=vy[i][0]+dt*ace(2,0,i,masas,x,y,z);
        vz[i][1]=vz[i][0]+dt*ace(3,0,i,masas,x,y,z);  
        
    }   
}
void gene(float* vx, float* vy, float* vz, float* x,  float* y,  float* z, float* masas, int tiempo){
    int i=0;
    for (i=0;i<10;i++){
        x[i][tiempo]=x[i][tiempo-2]+2*dt*vx[i][tiempo-1];
        y[i][tiempo]=y[i][tiempo-2]+2*dt*vy[i][tiempo-1];
        z[i][tiempo]=z[i][tiempo-2]+2*dt*vz[i][tiempo-1];
        vx[i][tiempo]=vx[i][tiempo-2]+2*dt*ace(1,tiempo-1,i,masas,x,y,z);
        vy[i][tiempo]=vy[i][tiempo-2]+2*dt*ace(2,tiempo-1,i,masas,x,y,z);
        vz[i][tiempo]=vz[i][tiempo-2]+2*dt*ace(3,tiempo-1,i,masas,x,y,z);  
        
    }   
    
    
}
double radio(float* x,  float* y,  float* z, int tiempo, int c, int c1){
    double radio=0;
    radio=sqrt((x[c][tiempo]-x[c1][tiempo])*(x[c][tiempo]-x[c1][tiempo])+(y[c][tiempo]-y[c1][tiempo])*(y[c][tiempo]-y[c1][tiempo])+(z[c][tiempo]-z[c1][tiempo])*(z[c][tiempo]-z[c1][tiempo]));
    return radio;
}
double ace(int pos, int tiempo, int p, float* masas,float* x,  float* y,  float* z){
    double a=0;
    double G = 1.985229E-29;
    int i=0;
    for (i=0;i<10;i++){
        if p!=i{
            if pos==1{
                a+=G*masas[i]*(x[p][tiempo]-x[i][tiempo])/pow(radio(x,y,z,tiempo,p,i),3);
            
            }
            if pos==1{
                a+=G*masas[i]*(y[p][tiempo]-y[i][tiempo])/pow(radio(x,y,z,tiempo,p,i),3);
            
            }
            if pos==1{
                a+=G*masas[i]*(z[p][tiempo]-z[i][tiempo])/pow(radio(x,y,z,tiempo,p,i),3);
            
            }
       
    
        }
    }
    return a;
}


    
