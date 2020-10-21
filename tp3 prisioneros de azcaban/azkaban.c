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
#define CANT_COMANDO_AYUDAS 2
#define CANT_COMANDO_PERDONABLES 3
#define CANT_COMANDO_LIBERAR 5
#define CANT_COMANDO_ACTUALIZAR 3
#define CANT_COMANDO_MOSTRAR_LIBERADOS 3
#define POS_COMANDO 1
#define POS_NOMBRE_ARCHIVO 2
#define POS_FECHA_LIBERADOS 3
#define POS_FECHA_ACTUALIZAR 2
#define POS_FECHA_MOSTRAR_LIBERADOS 2
#define POS_CONDICION 4


int main(int argc, char *argv[]){
    int estado;

        if(argc==CANT_COMANDO_AYUDAS && strcmp(argv[POS_COMANDO],COMANDO_AYUDAS)==0){

            mostrar_ayudas();

        }else if(argc==CANT_COMANDO_PERDONABLES && strcmp(argv[POS_COMANDO],COMANDO_PERDONABLES)==0){

            printf("\nIngresaste al comando perdonables\n");
            estado=perdonables(argv[POS_NOMBRE_ARCHIVO]);
            estado_archivo(estado);

        }else if(argc==CANT_COMANDO_LIBERAR && strcmp(argv[POS_COMANDO],COMANDO_LIBERAR)==0){

            printf("\nIngresaste al comando liberar\n");
            estado=liberados(argv[POS_NOMBRE_ARCHIVO],argv[POS_FECHA_LIBERADOS],*(argv[POS_CONDICION]));
            estado_archivo(estado);

        }else if(argc==CANT_COMANDO_ACTUALIZAR && strcmp(argv[POS_COMANDO],COMANDO_ACTUALIZAR)==0){

            printf("\nIngresaste al comando actualizar\n");
            estado=actualizar_archivos(argv[POS_FECHA_ACTUALIZAR]);
            estado_archivo(estado);

        }else if(argc==CANT_COMANDO_MOSTRAR_LIBERADOS && strcmp(argv[POS_COMANDO],COMANDO_MOSTRAR_LIBERADOS)==0){

            printf("Ingresaste al comando mostrar_liberados\n");
            estado=mostrar_liberados(argv[POS_FECHA_MOSTRAR_LIBERADOS]);
            estado_archivo(estado);

        }else{

            printf("El comando ingresado no existe, por favor ingrese uno correcto. Para saber cuales son los comandos y como funcionan ingrese el comando ayuda.\n");
        }

    return 0;
}
