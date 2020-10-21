#include "laberinto.h"
#include "copa.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define TAMANIO 15
#define GANO_JUGADOR 1
#define PERDIO_JUGADOR -1
#define SIGUE_JUEGO 0

//pre: Ninguna.
//pos: El procedimiento imprime por pantalla una expliacion del juego.
void explicar_juego(){
	printf("\n\n\nBIENVENIDO A LA TERCER PRUEBA DEL TORNEO DE LOS TRES MAGOS!!\n\n\n");
	printf("El juego consiste en encontrar la copa que se encuentra oculta en el laberinto antes del que rival la atrape.");
	printf("En el laberinto te vas a topar con obstaculos que te restaran puntos de vida, pero a no desesperarse! ya que tambien contaras ");
	printf("con hechizos que evitaran el danio de estos obstaculos y pociones que te daran vida.\n");
	printf("\nJ(jugador), G(rival)\n");
	printf("\nObstaculos: A(acromantula),E(escreguto) y B(boggart)\n");
	printf("\nAyudas: I(impedimenta), R(riddikulus), E(esfinge), P(pociones)\n");
}

//pre: Ninguna.
//pos: El procedimiento imprime por pantalla al usuario cuanta vida tiene y las ayudas que posee en su mochila.
void mostrar_informacion_al_jugador(jugador_t jugador){
	printf("\n punto de vida: %i\n ", jugador.vida);
	for(int i=0;i<jugador.tope_ayudas;i++){
		printf(" \n mochila del jugado: %c \n" ,jugador.ayudas[i].codigo);
	}

}
//pre: Ninguna.
//pos: El procedimiento le pide al usuario, por consola, que igrese una letra y en caso de no ser valido lepide que ingrese otra.
void ingresar_movimiento_jugador(juego_t juego,char *direccion){
	do{
		printf(" \n ingrese una letra \n 'd'= derecha \n 'a'= izquierda \n 'w'=arriba \n 's'=abajo \n ");
		scanf(" %c", direccion);
	}while(es_movimiento_valido(&juego,*direccion)==false);
}

int main(){
	juego_t juego;
	char laberinto[TAMANIO][TAMANIO];
	char direccion;
	srand((unsigned int)time(NULL));
	inicializar_laberinto(&juego);
	explicar_juego();
	actualizar_laberinto(juego, laberinto);
	mostrar_laberinto(laberinto);

	do{
			mostrar_informacion_al_jugador(juego.jugador);
			ingresar_movimiento_jugador(juego,&direccion);
			mover_jugador(&juego.jugador,direccion);
			if(estado_juego(juego)==0){
				mover_rival(&juego);
			}
			actualizar_juego(&juego);
			actualizar_laberinto(juego,laberinto);
			system("clear");
			mostrar_laberinto(laberinto);

	}while(estado_juego(juego)==SIGUE_JUEGO);

	if(estado_juego(juego)==GANO_JUGADOR){
			printf("Ganaste :) has conseguido la copa!!\n");
	}else if(estado_juego(juego)==PERDIO_JUGADOR){
			if(juego.jugador.vida<=0){
				printf(" Perdiste!te has quedado sin vida, suerte la proxima.\n");
			}else{
				printf("Perdiste!, el rival ha conseguido la copa.\n");
			}

		}
	return 0;
}
