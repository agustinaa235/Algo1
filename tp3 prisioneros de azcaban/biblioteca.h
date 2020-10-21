#ifndef _AZKABAN_H_
#define _AZKABAN_H_

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
} preso_t;

/*
*pre:Ninguna.
*pos: mostrara por consola el funcionamiento de cada comando.
*/

void mostrar_ayudas();

/*
*pre: La funcion recibe el nombre del archivo valido.
*pos: La funcion devolvera un numero negativo si no pudo abrir algun archivo, sino devolvera 1 en caso de que halla podido crear el archivo de
*    de perdonables.
*/

int perdonables(char nombre_perdonables[MAX_NOMBRE]);

/*
* pre: La funcion recibe el nombre del archivo valido, la fecha valida y una conducta valida(buena, regular o mala).
*pos: La funcion devolvera negativo si no pudo abrir algun archivo o 1 en caso de haber podido crear el archivo de liberados.
*/

int liberados(char nombre_perdonables[MAX_NOMBRE],char fecha_ingresada[MAX_FECHA], char conducta_ingresa);

/*
*pre: La funcion recibe la fecha ingresada por el usuario valida.
*pos: La funcion devolvera un numero negativo en caso de no haber podido acceder a algun archivo, sino deolvera 1 si pudo actualizar
*     correctamente a los archivos crucio, e imperius.
*/

int actualizar_archivos(char fecha_ingresada[MAX_FECHA]);

/*
*pre: La funcion recibira una fecha ingresada por el usuario valida.
*pos: La funcion devulve un numero negativo en caso de que no pudo acceder al archivo liberados, sino devolvera 1 si pude mostrar por pantalla exitosamente
*     a los presos que fueron liberados.
*/

int mostrar_liberados(char fecha_ingresada[MAX_FECHA]);

/*
*pre: El procecimiento recibe un estado valido;
*pos: El procecimiento mostrara por consola el estado del archivo ya sea si se pudo abrir exitosamente o si no pudo abrir determinado archivo.
*/
void estado_archivo(int estado);

#endif /* _AZKABAN_H_*/
