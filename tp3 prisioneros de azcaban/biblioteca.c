#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"
#include <stdbool.h>
#define BUENA 'B'
#define REGULAR 'R'
#define MALA 'M'
#define ARCHIVO_CRUCIO "crucio.dat"
#define ARCHIVO_IMPERIUS "imperius.dat"
#define ARCHIVO_LIBERADOS "liberados_"
#define MAX_NOMBRE 200
#define MAX_FECHA 7
#define EXITO 1
#define ERROR_IMPERIUS -1
#define ERROR_CRUCIO -2
#define ERROR_PERDONABLES -3
#define ERROR_LIBERADOS -4
#define PERDONABLES_NO_EXISTE -5
#define LIBERADOS_YA_EXISTE -6
#define ERROR_IMPERIUS_AUXILIAR -7
#define ERROR_CRUCIO_AUXILIAR -8
#define LIBERADOS_NO_EXISTE -9
#define ERROR_DE_FECHA -10



/*
*pre: Ninguna.
*post: El procedimiento mostrara por pantalla la explicacion del comando perdonables.
*/

void comando_perdonables();

/*
*pre: Ninguna.
*post: El procedimiento mostrara por pantalla la explicacion del comando liberar.
*/

void comando_liberar();

/*
*pre: Ninguna.
*post: El procedimiento mostrara por pantalla la explicacion del comando actualizar.
*/

void comando_actualizar();

/*
*pre: Ninguna.
*post: El procedimiento mostrara por pantalla la explicacion del comando mostrar liberados.
*/

void comando_mostrar_liberados();

/*
*pre: El procedimiento recibe dos strings, uno representa la fecha(valida) y el otro el nombre .
*post: El procecimiento generara el nombre del archivo siguiendo el formato liberados_aaaammm.txt.
*/

void obtener_nombre_liberados(char fecha_ingresada[MAX_FECHA], char nombre_archivo_liberados[MAX_NOMBRE]);

/*
*pre: La funcion recibe el archivo ya abierto.
*post: La funcion devuleve 0 si no leyo, sino devuelve la cantidad de presos que leyo.
*/
size_t leer_preso(FILE* archivo, preso_t *preso);

/*
*pre: El procedimiento recibe un archivo ya abierto.
*post: El procecimiento escribe al preso recibido en el archivo.
*/

void escribir_preso(FILE* archivo, preso_t preso);

/*
*pre: La funcion recibe un archivo ya abierto.
*post: La funcion vuelve 0 si no leyo nada, sino devuelve la cantidad de presos que leyo.
*/

int leer_preso_en_texto(FILE* archivo, char nombre[MAX_NOMBRE]);

/*
*pre: El procedimiento recibe un archivo ya abierto.
*post: El procedimiento escribe al preso en el archivo de texto.
*/

void escribir_preso_en_texto(FILE* archivo, preso_t preso);

/*
*pre: La funcion recibe dos nombres validos.
*post: La funcion devolvera 0 si los nombres son iguales, un numero mayor a cero si el primer nombre es mas grande que el segundo o menor
*     menor que cero si el primer nombre es menor que el segundo.
*/

int comparar( char nombre1[MAX_NOMBRE],char nombre2[MAX_NOMBRE]);

/*
*pre: La funcion recibe el nombre del archivo valido.
*post: La funcion devolvera true si el archivo ya existe, sino devolvera false en caso de que no exista.
*/

bool existe_archivo(const char nombre_archivo[MAX_NOMBRE]);

/*
*pre: El procedimiento recibe los archivos de imperius, crucio y perdonables ya abiertos.
*post: El procedimeinto escribe a los presos correspondientes(los que no estan en ambos archivos(crucio e imperius))
*      en el archivo perdonables.
*/

void diferencia_archivos(FILE* archivo_imperius, FILE* archivo_crucio, FILE* archivo_perdonables);

/*
*pre: El procedimiento recibe los archivo perdonables y liberados ya abiertos.
*     Recibe una fecha ingresada por el usuario  valida y una conducta valida((B)uena,(R)egular,(M)ala).
*post: El procedimiento escribe a los presos que van a ser liberaros en el archivo liberados de acuerdo a las
      condiciones ingresadas por el usurario.
*/

void filtrar_presos(FILE* archivo_perdonables, FILE* archivo_liberados, char fecha_ingresada[MAX_FECHA], char conducta_ingresada);

/*
*pre: La funcion recibe los archivos crucio, imperius y liberados ya abiertos.
*post: La funcion devolvera un numero negativo en caso de no poder abrir los archivos auxiliares, sino devolvera 1 si pudo crear los archivos auxiliares y
      y copiar a los presos que no estan en el archivo liberados en los archivos auxiliares.
*/

int eliminar_preso(FILE* archivo_crucio, FILE* archivo_imperius,FILE* archivo_liberados);

/*
*pre: El procedimiento recibe un archivo ya abierto.
*post: El procecimiento mostrara por pantalla a los presos liberados.
*/

void imprimir_nombre_presos(FILE* archivo_a_mostrar);



void comando_perdonables(){
    printf("\nComando perdonables:\n");
    printf("\nEste comando creara un archivo con todos los posibles presos a liberar. En este comando es necesario ingresar el nombre que desea ponerle al archivo.");
    printf(" Primero debera \ningresar el comando perdonables seguido por el nombre deseado del archivo a crear.\n");
    printf("Ejemplo:\n ./azkaban perdonables <nombre del archivo>\n");
}

void comando_liberar(){
    printf("\nComando liberar:\n");
    printf("\nEste comando creara un archivo de texto con los nombres de los presos que cumplan con las condiciones que usted ingresa (fecha y conducta) ");
    printf("para ser liberados. En este comando es necesario haber ejecutado previamente el comando perdonar, ingresar el nombre del archivo perdonable que ingreso en el comando anterior, la fecha deseada ");
    printf("y una conducta:(B)uena,(R)egular o (M)ala. Primero debera ser ingreado el comando liberar, seguido por el nombre del archivo, seguido por la fecha desea(esta tiene formato de aaaamm), seguido por la conducta.\n");
    printf("Ejemplo: \n ./azkaban liberar <nombre del archivo> <fecha> <conducta>\n");
}

void comando_actualizar(){

    printf("\nComando actualizar:\n");
    printf("\nEste comando actualizara ambos archivos(crucio e imperius),es decir, eliminara del sistema a los presos que fueron liberados por el comando anterior.");
    printf("En este comando es necesario haber ejecutado previamente el comando liberar y perdonables e ingresar la fecha que se utilizo previamente en el comando liberar. ");
    printf("Primero debera ejecutar el \ncomando actualizar seguido por la fecha .\n");
    printf("Ejemplo:\n ./azkaban actualizar <fecha>\n");
}

void comando_mostrar_liberados(){

    printf("\nComando mostrar_liberados:\n");
    printf("\nEste comando le mostrara por consola a los presos liberados por un determiando anio/mes. En este comando es \nnecesario haber ejecutado previamente el comando liberar y perdonables e ");
    printf("ingresar la misma fecha que utilizo en el comando liberar. Primero debera ingresar el \ncomando mostrar ayudas seguido por la fecha.\n");
    printf("Ejemplo:\n ./azkaban mostrar_liberados <fecha>\n");
}

void mostrar_ayudas(){

    printf("\nEstas son sus ayudas:\n");
    comando_perdonables();
    comando_liberar();
    comando_actualizar();
    comando_mostrar_liberados();
}

void estado_archivo(int estado){

    if(estado==ERROR_IMPERIUS){
        printf("Error de apertura del archivo imperius\n");
    }else if(estado==ERROR_CRUCIO){
        printf("Error de apertura del archivo crucio\n");
    }else if(estado==ERROR_PERDONABLES){
        printf("Error de apertura del archivo perdonables\n");
    }else if(estado==ERROR_PERDONABLES){
        printf("Error de apertura del archivo liberados\n");
    }else if(estado==PERDONABLES_NO_EXISTE){
        printf("El archivo perdonables no existe\n");
    }else if(estado==LIBERADOS_YA_EXISTE){
        printf("El archivo liberados ya existe con la fecha ingresada. Por favor ingrese otra fecha\n");
    }else if(estado==LIBERADOS_NO_EXISTE){
        printf("El archivo liberados no existe con la fecha ingresada.");
    }else if(estado==ERROR_DE_FECHA){
        printf("El archivo liberados con la fecha ingresada no existe.");
    }else if(estado==EXITO){
        printf("Accediste al archivo exitosamente\n");
    }
}

void obtener_nombre_liberados(char fecha_ingresada[MAX_FECHA], char nombre_archivo_liberados[MAX_NOMBRE]){

    strcpy(nombre_archivo_liberados,ARCHIVO_LIBERADOS);
    strcat(nombre_archivo_liberados,fecha_ingresada);
    strcat(nombre_archivo_liberados,".txt");
}

size_t leer_preso(FILE* archivo, preso_t *preso){

    return fread(preso,sizeof(preso_t),1,archivo);
}

void escribir_preso(FILE* archivo, preso_t preso){

    fwrite(&preso,sizeof(preso_t),1,archivo);
}

void escribir_preso_en_texto(FILE* archivo, preso_t preso){

    fprintf(archivo,"%s\n",preso.nombre);
}

int leer_preso_en_texto(FILE* archivo, char nombre[MAX_NOMBRE]){

    return fscanf(archivo,"%[^\n]\n",nombre);
}

int comparar( char nombre1[MAX_NOMBRE],char nombre2[MAX_NOMBRE]){

    return strcmp(nombre1,nombre2);
}


bool existe_archivo(const char nombre_archivo[MAX_NOMBRE]){

    bool ya_existe=true;
    FILE* archivo=fopen(nombre_archivo,"r");
        if(archivo==NULL){
            ya_existe=false;
        }else{
            fclose(archivo);
        }

    return ya_existe;
}

void diferencia_archivos(FILE* archivo_imperius, FILE* archivo_crucio, FILE* archivo_perdonables){

    preso_t preso_imperius;
    preso_t preso_crucio;
    size_t leidos_imperius, leidos_crucio;

    leidos_imperius= leer_preso(archivo_imperius,&preso_imperius);
    leidos_crucio= leer_preso(archivo_crucio,&preso_crucio);

      while(leidos_imperius>0 && leidos_crucio>0){

          if(comparar(preso_imperius.nombre,preso_crucio.nombre)<0){
              escribir_preso(archivo_perdonables,preso_imperius);
              leidos_imperius= leer_preso(archivo_imperius,&preso_imperius);

          }else if(comparar(preso_imperius.nombre,preso_crucio.nombre)>0){
              escribir_preso(archivo_perdonables,preso_crucio);
              leidos_crucio= leer_preso(archivo_crucio,&preso_crucio);

          }else{
              leidos_imperius= leer_preso(archivo_imperius,&preso_imperius);
              leidos_crucio= leer_preso(archivo_crucio,&preso_crucio);
          }
      }
      while(leidos_imperius>0){

              escribir_preso(archivo_perdonables,preso_imperius);
              leidos_imperius= leer_preso(archivo_imperius,&preso_imperius);
      }
      while(leidos_crucio>0){

              escribir_preso(archivo_perdonables,preso_crucio);
              leidos_crucio= leer_preso(archivo_crucio,&preso_crucio);
      }

}

int perdonables(char nombre_perdonables[MAX_NOMBRE]){

    FILE * archivo_imperius=fopen(ARCHIVO_IMPERIUS,"r");
        if(!archivo_imperius){
            return ERROR_IMPERIUS;
        }

    FILE* archivo_crucio=fopen(ARCHIVO_CRUCIO,"r");
        if(!archivo_crucio){
            fclose(archivo_imperius);
            return ERROR_CRUCIO;
        }

    FILE * archivo_perdonables=fopen(nombre_perdonables,"w");
        if(!archivo_perdonables){
            fclose(archivo_imperius);
            fclose(archivo_crucio);
            return ERROR_PERDONABLES;
        }

    diferencia_archivos(archivo_imperius,archivo_crucio, archivo_perdonables);

    fclose(archivo_imperius);
    fclose(archivo_crucio);
    fclose(archivo_perdonables);
    return EXITO;

}

void filtrar_presos(FILE* archivo_perdonables, FILE* archivo_liberados, char fecha_ingresada[MAX_FECHA], char conducta_ingresada){

    preso_t preso_perdonable;
    size_t leidos_perdonables;
    leidos_perdonables=leer_preso(archivo_perdonables,&preso_perdonable);

      while(leidos_perdonables>0){

          int comparacion= comparar(preso_perdonable.fecha,fecha_ingresada);
          if(comparacion==0 || comparacion<0){
                if(conducta_ingresada==BUENA && preso_perdonable.conducta==BUENA){
                    escribir_preso_en_texto(archivo_liberados,preso_perdonable);
                }else if(conducta_ingresada==REGULAR && (preso_perdonable.conducta==BUENA || preso_perdonable.conducta==REGULAR)){
                    escribir_preso_en_texto(archivo_liberados,preso_perdonable);
                }else if(conducta_ingresada==MALA){
                    escribir_preso_en_texto(archivo_liberados,preso_perdonable);
                }
          }
          leidos_perdonables=leer_preso(archivo_perdonables,&preso_perdonable);
      }
}

int liberados(char nombre_perdonables[MAX_NOMBRE],char fecha_ingresada[MAX_FECHA], char conducta_ingresada){

    char nombre_archivo_liberados[MAX_NOMBRE];
    obtener_nombre_liberados(fecha_ingresada,nombre_archivo_liberados);

        if(existe_archivo(nombre_perdonables) && !existe_archivo(nombre_archivo_liberados)){
            FILE* archivo_perdonables=fopen(nombre_perdonables,"r");
                if(!archivo_perdonables){
                    return ERROR_PERDONABLES;
                }

            FILE* archivo_liberados=fopen(nombre_archivo_liberados,"w");
                if(!archivo_liberados){
                    fclose(archivo_perdonables);
                    return ERROR_LIBERADOS;
                }

            filtrar_presos(archivo_perdonables, archivo_liberados,fecha_ingresada,conducta_ingresada);

            fclose(archivo_perdonables);
            fclose(archivo_liberados);
            return EXITO;

        }else if(!existe_archivo(nombre_perdonables)){
            return PERDONABLES_NO_EXISTE;
        }else{
            return LIBERADOS_YA_EXISTE;
        }
}

int eliminar_preso(FILE* archivo_crucio, FILE* archivo_imperius,FILE* archivo_liberados){

    FILE* archivo_aux_imperius=fopen("imperius_aux.dat","w");
        if(!archivo_liberados){
            printf("Error apertura de archivo");
            return ERROR_IMPERIUS_AUXILIAR;
        }

    FILE* archivo_aux_crucio=fopen("crucio_aux.dat","w");
        if(!archivo_crucio){
            printf("Error apertura de archivo");
            return ERROR_CRUCIO_AUXILIAR;
        }

    preso_t preso_crucio;
    preso_t preso_imperius;
    preso_t preso_liberados;

    size_t leidos_imperius=leer_preso(archivo_imperius,&preso_imperius);
    size_t leidos_crucio=leer_preso(archivo_crucio,&preso_crucio);
    int leidos_liberados=leer_preso_en_texto(archivo_liberados,preso_liberados.nombre);

        while(leidos_imperius>0 && leidos_crucio>0 && leidos_liberados>0){

            if(comparar(preso_imperius.nombre,preso_crucio.nombre)<0 && comparar(preso_imperius.nombre,preso_liberados.nombre)<0){
                  escribir_preso(archivo_aux_imperius,preso_imperius);
                  leidos_imperius=leer_preso(archivo_imperius,&preso_imperius);

            }else if(comparar(preso_imperius.nombre,preso_crucio.nombre)<0 && comparar(preso_imperius.nombre,preso_liberados.nombre)==0){
                  leidos_imperius=leer_preso(archivo_imperius,&preso_imperius);
                  leidos_liberados=leer_preso_en_texto(archivo_liberados,preso_liberados.nombre);

            }else if(comparar(preso_imperius.nombre,preso_crucio.nombre)>0 && comparar(preso_crucio.nombre,preso_liberados.nombre)<0){
                  escribir_preso(archivo_aux_crucio,preso_crucio);
                  leidos_crucio=leer_preso(archivo_crucio,&preso_crucio);

            }else if(comparar(preso_imperius.nombre,preso_crucio.nombre)>0 && comparar(preso_crucio.nombre,preso_liberados.nombre)==0){
                  leidos_crucio=leer_preso(archivo_crucio,&preso_crucio);
                  leidos_liberados=leer_preso_en_texto(archivo_liberados,preso_liberados.nombre);

            }else{
                  escribir_preso(archivo_aux_imperius,preso_imperius);
                  escribir_preso(archivo_aux_crucio,preso_crucio);
                  leidos_imperius=leer_preso(archivo_imperius,&preso_imperius);
                  leidos_crucio=leer_preso(archivo_crucio,&preso_crucio);
            }
        }
        while(leidos_imperius>0 && leidos_liberados>0){

            if(comparar(preso_imperius.nombre,preso_liberados.nombre)<0){
                escribir_preso(archivo_aux_imperius,preso_imperius);
                leidos_imperius=leer_preso(archivo_imperius,&preso_imperius);

            }else if(comparar(preso_imperius.nombre,preso_liberados.nombre)==0){
                leidos_imperius=leer_preso(archivo_imperius,&preso_imperius);
                leidos_liberados=leer_preso_en_texto(archivo_liberados,preso_liberados.nombre);
              }
        }
        while(leidos_crucio>0 && leidos_liberados>0){

            if(comparar(preso_crucio.nombre,preso_liberados.nombre)<0){
                escribir_preso(archivo_aux_crucio,preso_crucio);
                leidos_crucio=leer_preso(archivo_crucio,&preso_crucio);

            }else if(comparar(preso_crucio.nombre,preso_liberados.nombre)==0){
                leidos_crucio=leer_preso(archivo_crucio,&preso_crucio);
                leidos_liberados=leer_preso_en_texto(archivo_liberados,preso_liberados.nombre);
            }
        }
        while (leidos_imperius>0){

              escribir_preso(archivo_aux_imperius,preso_imperius);
              leidos_imperius=leer_preso(archivo_imperius,&preso_imperius);
        }
        while(leidos_crucio>0){

              escribir_preso(archivo_aux_crucio,preso_crucio);
              leidos_crucio=leer_preso(archivo_crucio,&preso_crucio);
        }

    fclose(archivo_aux_imperius);
    fclose(archivo_aux_crucio);
    return EXITO;
}

int actualizar_archivos(char fecha_ingresada[MAX_FECHA]){

    char nombre_archivo_liberados[MAX_NOMBRE];
    obtener_nombre_liberados(fecha_ingresada,nombre_archivo_liberados);

    FILE* archivo_imperius=fopen(ARCHIVO_IMPERIUS,"r");
        if(!archivo_imperius){
            return ERROR_IMPERIUS;
        }

    FILE* archivo_crucio=fopen(ARCHIVO_CRUCIO,"r");
        if(!archivo_crucio){
            fclose(archivo_imperius);
            return ERROR_CRUCIO;
        }

    FILE* archivo_liberados=fopen(nombre_archivo_liberados,"r");
        if(!archivo_liberados){
            fclose(archivo_imperius);
            fclose(archivo_crucio);
            return ERROR_LIBERADOS;
        }

    int estado=eliminar_preso(archivo_crucio,archivo_imperius,archivo_liberados);

    fclose(archivo_imperius);
    fclose(archivo_crucio);
    fclose(archivo_liberados);

    remove(ARCHIVO_IMPERIUS);
    remove(ARCHIVO_CRUCIO);
    rename("imperius_aux.dat",ARCHIVO_IMPERIUS);
    rename("crucio_aux.dat",ARCHIVO_CRUCIO);
    return estado;

}

void imprimir_nombre_presos(FILE* archivo_a_mostrar){

    preso_t preso_libre;
    int leidos=leer_preso_en_texto(archivo_a_mostrar, preso_libre.nombre);

        while(leidos>0){
            printf("%s\n", preso_libre.nombre);
            leidos=leer_preso_en_texto(archivo_a_mostrar, preso_libre.nombre);
        }
}

int mostrar_liberados(char fecha_ingresada[MAX_FECHA]){

    char nombre_archivo_liberados[MAX_NOMBRE];
    obtener_nombre_liberados(fecha_ingresada, nombre_archivo_liberados);

        if(existe_archivo(nombre_archivo_liberados)){
            FILE* archivo_liberados=fopen(nombre_archivo_liberados,"r");
                if(!archivo_liberados){
                    return ERROR_LIBERADOS;
                }
            printf("\nLos presos que fueron liberados el %s:\n\n", fecha_ingresada);
            imprimir_nombre_presos(archivo_liberados);

            fclose(archivo_liberados);
            return EXITO;
        }else{
            return ERROR_DE_FECHA;
        }
}
