#include<stdio.h>



#define MAX_NOMBRE 200
#define MAX_FECHA 7

typedef struct preso{
  char nombre[MAX_NOMBRE];
  unsigned int edad;
  char conducta;
  unsigned int pabellon;
  unsigned int celda;
  char fecha[MAX_FECHA];
  int maldicion_realizada;
}preso_t;

  int main(){
    preso_t preso;
    FILE* presos_imperius=fopen("crucio.txt","r");
    if(!presos_imperius){
      printf("No se ha podidio abrir el archivo");
      return 0;
    }
    FILE* imperius_bin=fopen("crucio.dat","w");
    if(!imperius_bin){
        printf("Error");
        fclose(presos_imperius);
      return 0;
    }
    int leido= fscanf(presos_imperius,"%[^;];%u;%c;%u;%u;%[^;];%i\n",preso.nombre,&(preso.edad),&(preso.conducta),&(preso.pabellon),&(preso.celda),preso.fecha,&(preso.maldicion_realizada));
    while(leido==7){
        fwrite(&preso,sizeof(preso_t),1,imperius_bin);
        printf("%s;%u;%c;%u;%u;%s;%i\n", preso.nombre,preso.edad,preso.conducta,preso.pabellon,preso.celda,preso.fecha,preso.maldicion_realizada);
        leido= fscanf(presos_imperius,"%[^;];%u;%c;%u;%u;%[^;];%i\n",preso.nombre,&(preso.edad),&(preso.conducta),&(preso.pabellon),&(preso.celda),preso.fecha,&(preso.maldicion_realizada));
      }
      fclose(presos_imperius);
      fclose(imperius_bin);

  }
