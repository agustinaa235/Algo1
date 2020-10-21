#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "laberinto.h"
#include "copa.h"
#include <stdlib.h>
#include <math.h>

#define JUGADOR 'J'
#define RIVAL 'G'
#define COPA 'C'
#define POCIONES 'P'
#define IMPEDIMENTA 'I'
#define RIDDIKULUS 'R'
#define ESCREGUTO 'E'
#define ACROMANTULA 'A'
#define BOGGART 'B'
#define ESFINGE 'F'
#define IZQUIERDA 'a'
#define ABAJO 's'
#define DERECHA 'd'
#define ARRIBA 'w'
#define TAMANIO 15
#define MAX_COORDENADAS 30
#define PARED '#'
#define MAX_VIDA 50
#define DANIO_ESCREGUTO 20
#define DANIO_ACROMANTULA 10
#define DANIO_BOGGART 15
#define VIDA_POCIONES 15
#define MAXIMO_PASOS 16
#define GANO_JUGADOR 1
#define PERDIO_JUGADOR -1
#define SIGUE_JUEGO 0
#define GASTO_PASOS 3
#define DISTANCIA_MAXIMA 10
#define MINIMO 0
#define MINIMA_VIDA_MOVIMIENTO 3
#define VIDA_PARA_MOSTRAR_COPA 15

//pre: la funcion recibe la coordenada de la copa y la cooordenada del rival o la del jugador.
//pos: La funcion devuleve true si la distancia entre la copa y una coordenada es mayor que diez, sino devolvera false.
bool distancia_manhattan(coordenada_t coordenada, coordenada_t coordenada_copa){
  int diferencia= abs(coordenada_copa.fil - coordenada.fil) + abs(coordenada_copa.col - coordenada.col);
    if(diferencia>DISTANCIA_MAXIMA){
      return true;
    }else{
      return false;
    }
}
//pre: ninguna.
//pos: la funcion devuelve una coordenada aleatoria.
coordenada_t posicion_aleatoria(){
	coordenada_t coordenada_aleatoria;
	coordenada_aleatoria.fil= rand()%TAMANIO;
	coordenada_aleatoria.col= rand()%TAMANIO;

	return coordenada_aleatoria;
}
// pre: los topes de los vectores deben estar inicializados.
//pos: la funcion devuleve true si la coordenada es valida, sino devuleve false.
bool coordenada_valida(coordenada_t coordenada_elemento, coordenada_t coordenadas_ocupadas[], int *tope_coordenadas_ocupadas, char laberinto_original[TAMANIO][TAMANIO]){
    bool es_valido=true;
    int i=0;
    while(i<=(*tope_coordenadas_ocupadas) && es_valido){
      if((coordenadas_ocupadas[i].fil==coordenada_elemento.fil && coordenadas_ocupadas[i].col==coordenada_elemento.col)|| (laberinto_original[coordenada_elemento.fil][coordenada_elemento.col]== PARED)){
        es_valido=false;
      }
      i++;
    }

  return es_valido;
}
//pre: El procedimiento recibe el tope de coordenada ocupadas inicializado y el laberinto original ya viene cargado con las paredes del laberinto.
//pos: El procedimiento inicializa el elemento copa asignadole una posicon valida y el codigo.
void inicializar_copa(copa_t* copa, char laberinto_original[TAMANIO][TAMANIO], coordenada_t coordenadas_ocupadas[],int  *tope_coordenadas_ocupadas){
  copa->codigo= COPA;
  coordenada_t coordenada_copa;
  do{
    coordenada_copa= posicion_aleatoria();
  }while(coordenada_valida(coordenada_copa,coordenadas_ocupadas, tope_coordenadas_ocupadas,laberinto_original)==false);
    copa->posicion= coordenada_copa;
    coordenadas_ocupadas[(*tope_coordenadas_ocupadas)]=coordenada_copa;
    (*tope_coordenadas_ocupadas)++;

}
//pre: El procedimiento recbie el tope de obstaculos y coordenadas ocupadas inicializados y el laberinto original ya viene cargado con las paredes del laberinto.
//pos: El procedimiento inicializa el obstaculo que recibe asignandole una posicion valida, el codigo y el danio.
void inicializar_obstaculo(obstaculo_t obstaculos[], int (*tope_obstaculos), char laberinto_original[TAMANIO][TAMANIO], coordenada_t coordenadas_ocupadas[], int *tope_coordenadas_ocupadas, char obstaculo_codigo, int danio){
  obstaculos[(*tope_obstaculos)].codigo= obstaculo_codigo;
  obstaculos[(*tope_obstaculos)].danio= danio;
  coordenada_t coordenada_obstaculo;
  do{
    coordenada_obstaculo= posicion_aleatoria();
  }while(coordenada_valida(coordenada_obstaculo, coordenadas_ocupadas, tope_coordenadas_ocupadas,laberinto_original)==false);
    obstaculos[(*tope_obstaculos)].posicion= coordenada_obstaculo;
    coordenadas_ocupadas[(*tope_coordenadas_ocupadas)]=coordenada_obstaculo;
    (*tope_coordenadas_ocupadas)++;
    (*tope_obstaculos)++;
}
//pre: El procedimiento rebice el tope de obstaculos y coordenadas ocupadas inicalizados y el laberinto original ya viene cargado con las paredes del laberinto.
//pos: El procedimiento inicializara todos los obstaculos.
void inicializar_obstaculos(obstaculo_t obstaculos [],int *tope_obstaculos, char laberinto_original[TAMANIO][TAMANIO], coordenada_t coordenadas_ocupadas[],int *tope_coordenadas_ocupadas){

  inicializar_obstaculo(obstaculos,tope_obstaculos,laberinto_original,coordenadas_ocupadas,tope_coordenadas_ocupadas,ESCREGUTO,DANIO_ESCREGUTO);
  inicializar_obstaculo(obstaculos,tope_obstaculos,laberinto_original,coordenadas_ocupadas,tope_coordenadas_ocupadas,ACROMANTULA,DANIO_ACROMANTULA);
  inicializar_obstaculo(obstaculos,tope_obstaculos,laberinto_original,coordenadas_ocupadas,tope_coordenadas_ocupadas,BOGGART,DANIO_BOGGART);
}
//pre: El procedimiento rebice el tope de ayudas y coordenadas ocupadas inicalizados y el laberinto original ya viene cargado con las paredes del laberinto.
//pos: El procedimiento inicializara la ayuda que recibe asignandole una posicion valida, el codigo y su vida a recuperar.
void inicializar_ayuda(ayuda_t ayudas[], int (*tope_ayudas), char laberinto_original[TAMANIO][TAMANIO], coordenada_t coordenadas_ocupadas[], int *tope_coordenadas_ocupadas, char codigo, int vida_ayudas){
  ayudas[(*tope_ayudas)].codigo= codigo;
  ayudas[(*tope_ayudas)].vida_a_recuperar= vida_ayudas;
  coordenada_t coordenada_ayuda;
  do{
    coordenada_ayuda= posicion_aleatoria();
  }while(coordenada_valida(coordenada_ayuda, coordenadas_ocupadas, tope_coordenadas_ocupadas,laberinto_original)==false);
    ayudas[(*tope_ayudas)].posicion= coordenada_ayuda;
    coordenadas_ocupadas[(*tope_coordenadas_ocupadas)]=coordenada_ayuda;
    (*tope_coordenadas_ocupadas)++;
    (*tope_ayudas)++;

}
//pre: El procedimiento rebice el tope de ayudas y coordenadas ocupadas inicalizados y el laberinto original ya viene cargado con las paredes del laberinto.
//pos: El procedimiento inicializara todas las ayudas.
void inicializar_ayudas(ayuda_t ayudas[], int (*tope_ayudas), char laberinto_original[TAMANIO][TAMANIO], coordenada_t coordenadas_ocupadas[], int *tope_coordenadas_ocupadas){

  inicializar_ayuda(ayudas,tope_ayudas,laberinto_original, coordenadas_ocupadas, tope_coordenadas_ocupadas,IMPEDIMENTA,0);
  inicializar_ayuda(ayudas,tope_ayudas,laberinto_original, coordenadas_ocupadas, tope_coordenadas_ocupadas,RIDDIKULUS,0);
  inicializar_ayuda(ayudas,tope_ayudas,laberinto_original, coordenadas_ocupadas, tope_coordenadas_ocupadas,POCIONES,VIDA_POCIONES);
  inicializar_ayuda(ayudas,tope_ayudas,laberinto_original, coordenadas_ocupadas, tope_coordenadas_ocupadas,POCIONES,VIDA_POCIONES);
  inicializar_ayuda(ayudas,tope_ayudas,laberinto_original, coordenadas_ocupadas, tope_coordenadas_ocupadas,POCIONES,VIDA_POCIONES);
  inicializar_ayuda(ayudas,tope_ayudas,laberinto_original, coordenadas_ocupadas, tope_coordenadas_ocupadas,ESFINGE,0);

}
//pre: El procedimiento recibe el tope de coordenadas ocupadas inicializado y el laberinto original ya cargado con las paredes del laberinto.
//pos: El procedimiento incializa al rival asignandole una poscion valida y su codigo.
void inicializar_rival(rival_t* rival,coordenada_t copa,char laberinto_original[TAMANIO][TAMANIO], coordenada_t coordenadas_ocupadas[],int  *tope_coordenadas_ocupadas){
  rival->codigo= RIVAL;
  coordenada_t coordenada_rival;
  do{
    coordenada_rival= posicion_aleatoria();
  }while(coordenada_valida(coordenada_rival,coordenadas_ocupadas, tope_coordenadas_ocupadas,laberinto_original)== false || distancia_manhattan(coordenada_rival, copa)==false);
    rival->posicion= coordenada_rival;
    coordenadas_ocupadas[(*tope_coordenadas_ocupadas)]=coordenada_rival;
    (*tope_coordenadas_ocupadas)++;
  }
  //pre: El procedimiento recibe el tope de coordenadas ocupadas inicializado y el laberinto original ya cargado con las paredes del laberinto.
  //pos: El procedimento inicializa al jugador asignadole una posicion valida, su codigo y su vida.
  void inicializar_jugador(jugador_t* jugador,coordenada_t copa,char laberinto_original[TAMANIO][TAMANIO], coordenada_t coordenadas_ocupadas[],int  *tope_coordenadas_ocupadas){
    jugador->codigo= JUGADOR;
    jugador->vida=MAX_VIDA;
    coordenada_t coordenada_jugador;
    do{
      coordenada_jugador= posicion_aleatoria();
    }while(coordenada_valida(coordenada_jugador,coordenadas_ocupadas, tope_coordenadas_ocupadas,laberinto_original) == false || distancia_manhattan(coordenada_jugador, copa)==false);
      jugador->posicion= coordenada_jugador;
      coordenadas_ocupadas[(*tope_coordenadas_ocupadas)]=coordenada_jugador;
      (*tope_coordenadas_ocupadas)++;

}
void inicializar_laberinto(juego_t* juego){

   coordenada_t coordenadas_ocupadas[MAX_COORDENADAS];
   int tope_coordenadas_ocupadas =0;
   juego->tope_obstaculos=0;
   juego->tope_ayudas=0;
   juego->rival.cantidad_pasos=0;
   juego->jugador.tope_ayudas=0;
   inicializar_paredes_laberinto(juego->laberinto_original);

	inicializar_copa(&juego->copa,juego->laberinto_original, coordenadas_ocupadas, &tope_coordenadas_ocupadas);
  inicializar_obstaculos(juego->obstaculos,&juego->tope_obstaculos, juego->laberinto_original, coordenadas_ocupadas, &tope_coordenadas_ocupadas);
  inicializar_ayudas(juego->ayudas,&juego->tope_ayudas, juego->laberinto_original,coordenadas_ocupadas,&tope_coordenadas_ocupadas);
  inicializar_rival(&juego->rival,juego->copa.posicion,juego->laberinto_original, coordenadas_ocupadas, &tope_coordenadas_ocupadas);
	inicializar_jugador(&juego->jugador, juego->copa.posicion,juego->laberinto_original, coordenadas_ocupadas, &tope_coordenadas_ocupadas);
}
//pre: El procedimiento recibe el laberinto original con las paredes del laberinto ya inicializadas.
//pos: El procedimeinto posiciona en mi laberinto auxiliar las paredes.
void posicionar_paredes(char laberinto_original[TAMANIO][TAMANIO], char laberinto[TAMANIO][TAMANIO]){
  for(int i=0;i<TAMANIO;i++){
		for(int j=0;j<TAMANIO;j++){
			laberinto[i][j]=laberinto_original[i][j];
		}
}
}
//pre: El procedimiento recibe el laberinto con las paredes ya inicializadas, el vector de obstaculos ya cargado y su tope ya inicalizado.
//pos: El procedimiento posiciona los obstaculos en mi labento auxiliar.
void posicionar_obstaculos(obstaculo_t obstaculos[], int tope_obstaculos, char laberinto[TAMANIO][TAMANIO]){
  for(int i=0;i<tope_obstaculos;i++){
    laberinto[obstaculos[i].posicion.fil][obstaculos[i].posicion.col]=obstaculos[i].codigo;
  }
}
//pre: El procedimiento recibe el laberinto con las paredes ya inicializadas, el vector de ayudas ya cargado y su tope ya inicalizado.
//pos: El procedimiento posiciona las ayudas en mi laberinto auxiliar.
void posicionar_ayudas(ayuda_t ayudas[],int tope_ayudas, char laberinto[TAMANIO][TAMANIO]){
  for(int i=0;i<tope_ayudas;i++){
    laberinto[ayudas[i].posicion.fil][ayudas[i].posicion.col]=ayudas[i].codigo;
  }
}
//pre: El procedimiento recibe el laberinto con las paredes ya inicializadas.
//pos: El procedimeinto posicionara al jugador en mi laberinto auxiliar.
void posicionar_jugador(jugador_t jugador, char laberinto[TAMANIO][TAMANIO]){
  laberinto[jugador.posicion.fil][jugador.posicion.col]=jugador.codigo;
}
//pre: El procedimiento recibe el laberinto con las paredes ya inicializadas.
//pos: El procedimeinto posicionara al rival en mi laberinto auxiliar.
void posicionar_rival(rival_t rival, char laberinto [TAMANIO][TAMANIO]){
  laberinto[rival.posicion.fil][rival.posicion.col]=rival.codigo;
}
//pre: El procedimiento recibe el laberinto con las paredes ya inicializadas.
//pos: El procedimeinto posicionara la copa en mi laberinto auxiliar.
void posicionar_copa(copa_t copa, char laberinto[TAMANIO][TAMANIO]){
  laberinto[copa.posicion.fil][copa.posicion.col]=copa.codigo;
}
//pre: El tope de ayudas del juagdor ya viene inicalizado.
//pos: La funcion devolvera true si el jugador pose la esfinge, en caso contrario devolvera false.
bool encontro_la_esfinge(ayuda_t ayudas_jugador[], int tope_ayudas_jugador){
    bool encontro=false;
    for(int i=0;i<tope_ayudas_jugador;i++){
      if(ayudas_jugador[i].codigo==ESFINGE){
        encontro=true;
      }
    }
    return encontro;
}
//pre: El procedimiento recibe el laberinto con las paredes ya inicializadas.
//pos: El procedimie
void actualizar_laberinto(juego_t juego, char laberinto[TAMANIO][TAMANIO]){
    posicionar_paredes(juego.laberinto_original, laberinto);
    posicionar_obstaculos(juego.obstaculos,juego.tope_obstaculos,laberinto);
    posicionar_ayudas(juego.ayudas,juego.tope_ayudas,laberinto);
    posicionar_rival(juego.rival, laberinto);
    posicionar_jugador(juego.jugador, laberinto);


    if(encontro_la_esfinge(juego.jugador.ayudas,juego.jugador.tope_ayudas)|| juego.jugador.vida<=VIDA_PARA_MOSTRAR_COPA){
      posicionar_copa(juego.copa, laberinto);
    }
}
//pre: ninguna.
//pos: La funcion devuleve true si el movimiento es valido, sino devolvera false.
bool es_movimiento_valido(juego_t* juego, char tecla){
  coordenada_t posible_posicion= juego->jugador.posicion;
  bool es_valido=false;
    if((tecla==DERECHA) && juego->laberinto_original[posible_posicion.fil][posible_posicion.col+1]!= PARED && (posible_posicion.col+1)<TAMANIO){
      es_valido=true;
    }else if((tecla== IZQUIERDA) && juego->laberinto_original[posible_posicion.fil][posible_posicion.col-1]!= PARED && (posible_posicion.col-1)>=MINIMO){
      es_valido=true;
    }else if((tecla== ARRIBA) && juego->laberinto_original[posible_posicion.fil-1][posible_posicion.col]!= PARED && (posible_posicion.fil-1)>=MINIMO){
      es_valido=true;
    }else if((tecla== ABAJO) && juego->laberinto_original[posible_posicion.fil+1][posible_posicion.col]!= PARED && (posible_posicion.fil+1)<TAMANIO){
      es_valido=true;
    }
    return es_valido;
}

 void mover_jugador(jugador_t *jugador, char direccion){
   if(jugador->vida>=MINIMA_VIDA_MOVIMIENTO){
      switch(direccion){
        case DERECHA:
          jugador->posicion.col+=1;
          break;
        case IZQUIERDA:
           jugador->posicion.col-=1;
           break;
        case ARRIBA:
           jugador->posicion.fil-=1;
           break;
         case ABAJO:
           jugador->posicion.fil+=1;
           break;
         }
      }
}
//pre: la cantidad de pasos del rival ya esta inicializada.
//pos: El procedimeinto le asigna la direccion al rival de acuerdo a movimientos por turno.
void obtener_direccion_rival(rival_t* rival){

  int movimiento_por_turno = (rival->cantidad_pasos)% MAXIMO_PASOS;

  if((movimiento_por_turno>= 0 && movimiento_por_turno<= 3)){
    rival->direccion=DERECHA;
  }else if((movimiento_por_turno>3 && movimiento_por_turno<=7)){
    rival->direccion=ABAJO;
  }else if((movimiento_por_turno>7 && movimiento_por_turno<=11)){
    rival->direccion=IZQUIERDA;
  }else if((movimiento_por_turno>11 && movimiento_por_turno<=15)){
    rival->direccion= ARRIBA;
  }
}
//pre: La funcion recibe el laberinto original con las paredes ya inicializadas.
//pos: La funcion devuleve true si el movimiento es valido, sino devuelve false.
bool puede_moverse(rival_t rival, char laberinto_original[TAMANIO][TAMANIO], char direccion){
  bool es_valido=false;
  if((direccion==ABAJO) && (laberinto_original[rival.posicion.fil+1][rival.posicion.col]!='#') && (rival.posicion.fil+1<TAMANIO)){
    es_valido=true;
  }else if((direccion==ARRIBA) && (laberinto_original[rival.posicion.fil-1][rival.posicion.col]!='#')&& (rival.posicion.fil-1>=MINIMO)){
    es_valido=true;
  }else if((direccion== DERECHA) && (laberinto_original[rival.posicion.fil][rival.posicion.col+1]!='#')&& (rival.posicion.col+1<TAMANIO)){
    es_valido=true;
  }else if((direccion== IZQUIERDA) && (laberinto_original[rival.posicion.fil][rival.posicion.col-1]!='#')&&(rival.posicion.col-1>=MINIMO)){
    es_valido=true;
  }
  return es_valido;
}
void mover_rival(juego_t *juego){
  bool se_movio=false;
  do{
    obtener_direccion_rival(&(juego->rival));
      if(juego->rival.direccion==DERECHA && puede_moverse(juego->rival, juego->laberinto_original,juego->rival.direccion)){
          juego->rival.posicion.col+=1;
          se_movio=true;
        }else if(juego->rival.direccion== ABAJO && puede_moverse(juego->rival, juego->laberinto_original,juego->rival.direccion)){
          juego->rival.posicion.fil+=1;
          se_movio=true;
        }else if(juego->rival.direccion==IZQUIERDA && puede_moverse(juego->rival, juego->laberinto_original,juego->rival.direccion)){
          juego->rival.posicion.col-=1;
          se_movio=true;
        }else if(juego->rival.direccion==ARRIBA && puede_moverse(juego->rival, juego->laberinto_original,juego->rival.direccion)){
          juego->rival.posicion.fil-=1;
          se_movio=true;
        }
        juego->rival.cantidad_pasos+=1;
    }while(se_movio==false);

}
//pre: El procedimiento recibe una posicion valida(mayor o igual a 0) y el tope de obstaclos ya inicializado.
//pos: El procedimiento eliminimara del vector de obstaculos, el obstaculo que se encontraba en la posicion recibida.
void eliminar_obstaculos(obstaculo_t obstaculos[], int *tope_obstaculos, int posicion){

  for(int i=posicion; i<(*tope_obstaculos)-1;i++){
      obstaculos[i]=obstaculos[i+1];
  }
  (*tope_obstaculos)--;

}
//pre: El procedimiento recibe una posicion valida(mayor o igual a 0) y el tope de ayudas ya inicializado.
//pos: El procedimiento eliminimara del vector de ayudas, la ayuda que se encontraba en la posicion recibida.
void eliminar_ayudas(ayuda_t ayudas[], int *tope_ayudas, int posicion){

  for(int i=posicion; i<(*tope_ayudas)-1;i++){
      ayudas[i]=ayudas[i+1];
  }
  (*tope_ayudas)--;

}
//pre: El procedimeinto recibe el tope de ayudas del juagdor ya inicializado.
//pos: El procedimiento insertara la ayuda recibida en el vector de ayudas del juagdor.
void insertar_ayudas(ayuda_t ayudas_jugador[], int *tope_ayudas_jugador, ayuda_t ayuda_a_ingresar){
  ayudas_jugador[(*tope_ayudas_jugador)]= ayuda_a_ingresar;
  (*tope_ayudas_jugador)++;
}
//pre: El procedimeinto recibe el tope de ayudas del jugador ya inicializado.
//pos: El procedimiento actualizara las ayudas de la matriz si el jugador se encuentra en la misma posicion que una ayuda.
//     Esta ayuda sera eliminada y si no es una pocion esta sera insertada en el vector de ayudas del jugador.
void actualizar_ayudas(jugador_t *jugador, ayuda_t ayudas [], int *tope_ayudas){
  int posicion=-1;
  int posible_vida;
  for(int i=0;i<(*tope_ayudas);i++){
      if(ayudas[i].posicion.fil==jugador->posicion.fil && ayudas[i].posicion.col==jugador->posicion.col){
        posicion=i;
      }
    }
  if(posicion!=-1){
      if(ayudas[posicion].codigo==IMPEDIMENTA || ayudas[posicion].codigo==RIDDIKULUS || ayudas[posicion].codigo==ESFINGE){
        insertar_ayudas(jugador->ayudas,&jugador->tope_ayudas,ayudas[posicion]);
      }else if(ayudas[posicion].codigo==POCIONES){
        posible_vida= jugador->vida + ayudas[posicion].vida_a_recuperar;
          if(posible_vida>MAX_VIDA){
            jugador->vida=MAX_VIDA;
          }else{
            jugador->vida= posible_vida;
          }
        }
    eliminar_ayudas(ayudas,tope_ayudas,posicion);
  }
}
//pre: Ninguna.
//pos: La funcion devolvera true si el el jugador tiene en su vector de ayudas impedimenta y el jugador esta en la posicion del escreguto o si
//     tiene a riddikulus y el jugador se encuntra en la posicon de boggart, sino devolvera false.
bool ayuda_necesaria (jugador_t jugador,obstaculo_t obstaculo){
  bool tengo_ayuda=false;
  for(int i=0;i<jugador.tope_ayudas;i++){
    if(obstaculo.codigo==ESCREGUTO && jugador.ayudas[i].codigo==IMPEDIMENTA){
      tengo_ayuda=true;
    }else if(obstaculo.codigo==BOGGART && jugador.ayudas[i].codigo==RIDDIKULUS){
      tengo_ayuda=true;
    }
  }
  return tengo_ayuda;
}

//pre: El procedimeinto recibe el tope de obstaculos del jugador ya inicializado.
//pos: El procedimiento actualizara los obstaculos de la matriz si el jugador se encuentra en la misma posicion que un obstaculo.
//     Este obstculo sera eliminade del laberinto.
void actualizar_obstaculos(jugador_t *jugador, obstaculo_t obstaculos[], int *tope_obstaculos){
  int posicion=-1;
  for(int i=0;i<(*tope_obstaculos);i++){
      if(obstaculos[i].posicion.fil==jugador->posicion.fil && obstaculos[i].posicion.col== jugador->posicion.col){
        posicion=i;
        }
      }
    if(posicion!= -1){
        if(ayuda_necesaria(*jugador,obstaculos[posicion])==false){
          (jugador->vida)-=obstaculos[posicion].danio;
        }
      eliminar_obstaculos(obstaculos,tope_obstaculos,posicion);
    }
}
void actualizar_juego (juego_t* juego){
  juego->jugador.vida-= GASTO_PASOS;
  actualizar_ayudas(&juego->jugador,juego->ayudas, &juego->tope_ayudas);
  actualizar_obstaculos(&juego->jugador, juego->obstaculos,&juego->tope_obstaculos);

}
//pre:Ninguna.
//pos: La funcion devolvera true si el jugador o rival se encuentra en la misma posicion que la copa.
bool tiene_la_copa(coordenada_t coordenada, copa_t copa ){
  if(coordenada.fil==copa.posicion.fil && coordenada.col==copa.posicion.col){
    return true;
  }else{
    return false;
  }
}
int estado_juego (juego_t juego){
  bool jugador_tiene_la_copa= tiene_la_copa(juego.jugador.posicion,juego.copa);
  bool rival_tiene_la_copa= tiene_la_copa(juego.rival.posicion, juego.copa);
  if(jugador_tiene_la_copa){
    return GANO_JUGADOR;
  }else if( rival_tiene_la_copa || juego.jugador.vida<=0){
    return PERDIO_JUGADOR;
  }else{
    return SIGUE_JUEGO;
  }
}
void mostrar_laberinto( char laberinto[TAMANIO][TAMANIO]){
    for(int i=0;i<TAMANIO; i++){
      printf("\n");
      for(int j=0;j<TAMANIO; j++){
        printf(" %c", laberinto[i][j]);
      }
    }

  }
