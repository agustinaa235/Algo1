#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"
#define COMANDO_AYUDAS "ayuda"
#define COMANDO_PERDONABLES "perdonables"
#define COMANDO_LIBERAR "liberar"
#define COMANDO_ACTUALIZAR "actualizar"
#define COMANDO_MOSTRAR_LIBERADOS "mostrar_liberados"
#define MAX_NOMBRE 200
#define MAX_FECHA 7
#define POS_COMANDO 1
#define POS_NOMBRE_ARCHIVO 2
#define POS_FECHA_LIBERADOS 3
#define POS_FECHA_ACTUALIZAR 2
#define POS_FECHA_MOSTRAR_LIBERADOS 2



int main(int argc, char *argv[]){
      int estado;
      if(argc==1){
          printf("\nDevera ejercutar un comando. Para ver los comandos dispobles ingrese el comando ayuda.\n");
      }else if(strcmp(argv[POS_COMANDO],COMANDO_AYUDAS)==0 && argc==2){

          mostrar_ayudas();

      }else if(strcmp(argv[POS_COMANDO],COMANDO_PERDONABLES)==0 && argc==3){

          printf("\nIngresaste al comando perdonables\n");
          estado=perdonables(argv[POS_NOMBRE_ARCHIVO]);
          mostrar_archivo(argv[POS_NOMBRE_ARCHIVO]);
          estado_archivo(estado);


      }else if(strcmp(argv[POS_COMANDO],COMANDO_LIBERAR)==0 && argc==5){

          printf("\nIngresaste al comando liberar\n");
          estado=liberados(argv[POS_NOMBRE_ARCHIVO],argv[POS_FECHA_LIBERADOS],argv[4][0]);
          estado_archivo(estado);
      }else if(strcmp(argv[POS_COMANDO],COMANDO_ACTUALIZAR)==0 && argc==3){

          printf("\nIngresaste al comando actualizar\n");
          estado=actualizar_archivos(argv[POS_FECHA_ACTUALIZAR]);
          estado_archivo(estado);

      }else if(strcmp(argv[POS_COMANDO],COMANDO_MOSTRAR_LIBERADOS)==0 && argc==3){
          printf("Ingresaste al comando mostrar_liberados\n");
          estado=mostrar_liberados(argv[POS_FECHA_MOSTRAR_LIBERADOS]);
          estado_archivo(estado);

      }else{

          printf("El comando ingresado no existe, por favor ingrese uno correcto");
          mostrar_ayudas();
        }

    return 0;
}
