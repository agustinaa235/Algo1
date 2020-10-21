#include <stdio.h>

const int buena = 'B';
const int regular = 'R';
const int mala = 'M';





void obtener_edad_alumno(int *edad){

	do{
		printf("Ingresar edad del alumno ");
		scanf("%i", edad);
	} 
	while (!edad_valida(edad))
}
bool edad_valida(int edad){

	return(edad >= 17);
}

void obtener_inteligencia_alumno(int *inteligencia){

	do{
		printf("Ingresar inteligencia del alumno ");
		scanf("%i", inteligecia);
	}
	while(!inteligencia_validad(inteligecia))
}
bool inteligencia_validad(int inteligecia){

	return(inteligecia >= 0 && inteligecia<= 10)
}

void obtener_fuerza_alumno(int *fuerza){

	do{
		printf("Ingresar fuerza del alumno ");
		scanf("%i", fuerza);
	}
	while (!fuerza_validad(fuerza))
}
bool fuerza_valida(int fuerza){

	return(fuerza>=0 && fuerza<=10);
}

void obtener_capacidad_magica_alumno(char *capacidad_magica){
	do{
		printf("Ingrese capacidad magica ");
		scanf("%c", capacidad_magica);
	}
	while (!cantidad_magica_valida(capacidad_magica))
}
bool cantidad_magica_valida(char capacidad_magica){

	return (capacidad_magica == 'B' || capacidad_magica == 'R' || capacidad_magica == 'M');
}

int main(){

	int edad;
	int inteligecia;
	int fuerza;
	char capacidad_magica;
	obtener_edad_alumno(&edad);
	obtener_inteligencia_alumno(&inteligecia);
	obtener_fuerza_alumno(&fuerza);
	obtener_capacidad_magica_alumno(&capacidad_magica);

	return 0;

}