#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define NUM_CATEGORIAS 11
#define TURNOS 3
#define N 5

void reglas() {
    printf("REGLAS:\n");
    printf("\nEL JUEGO\n");
    printf(" Consiste en sumar la mayor cantidad de puntos, logrando la mayor cantidad de numeros: 1, 2, 3, 4, 5 y 6 colocados en el anotador en orden progresivo.\n");
    printf(" Ademas estan los juegos denominados mayores que son: Escalera, Full, Poker, Generala y Generala Doble.\n");
    printf(" Se juega con 5 dados.\n"); //Para decidir quién comienza el juego cada jugador arroja los 5 dados, el que obtenga el mayor puntaje sera el primero, lo seguira el de su derecha y asi sucesivamente
    printf("\nDESARROLLO DEL JUEGO\n");
    printf(" El primer jugador arroja los 5 dados y segun el resultado elige numeros repetidos u otra variante que le permita armar un juego.\n");
    printf(" Los dados que no le sirven puede volverlos a tirar repitiendo la accion anterior tratando de obtener mas numeros iguales o armar un juego.\n");
    printf(" Se puede tirar 3 veces por turno, luego se anotan los puntos obtenidos en la casilla correspondiente del anotador.\n");
    printf("\nJUEGOS MAYORES\n");
    printf(" Escalera se forma con 1 - 2 - 3 - 4 - 5 ; 2 - 3 - 4 - 5 - 6; 3 - 4 - 5 - 6 - 1\n");
    printf(" Full : se forma con 3 dados del mismo numero y 2 iguales de otro.\n");
    printf(" Poker : se forma con 4 dados de igual numero.\n");
    printf(" Generala : se forma con 5 dados de igual numero.\n");
    printf(" Generala Doble : se forma con 5 dados con el numero.\n");
    printf("\nGANADOR\n");
    printf(" Una vez que todos los jugadores hayan completado las casillas del anotador el ganador sera quien haya obtenido el mayor puntaje de la suma de todas las casillas.\n");
    printf(" En caso de igualar puntajes se declarara EMPATE.\n");
    printf("\nValores por logro:\n");
    printf(" 1 : Valor minimo 0 - valor maximo 5.\n");
    printf(" 2 : Valor minimo 0 - valor maximo 10.\n");
    printf(" 3 : Valor minimo 0 - valor maximo 15.\n");
    printf(" 4 : Valor minimo 0 - valor maximo 20.\n");
    printf(" 5 : Valor minimo 0 - valor maximo 25.\n");
    printf(" 6 : Valor minimo 0 - valor maximo 30.\n");
    printf(" E : La escalera lograda vale 35 puntos.\n");
    printf(" F : El full logrado vale 50 puntos.\n");
    printf(" P : El poker logrado vale 75 puntos.\n");
    printf(" G : La generala vale 100 puntos.\n");
    printf(" DG : La generala doble vale 120 puntos.\n");
}
void introduccion (){
         printf("\n\t\tAUS\t\t     2024\n\n\t\tTaller de programacion I\n\n\t\tTrabajo final : GENERALA\n\n\t\tMARINA MONSALVE-COMISION 1\t\t\t\n\n\t\t  [][][][][][][][][][]]\n\t\t  [][][][][][][][][][]]\n\t\t  [][][][][][][][][][]]\n\t\t             [][][][][]\n\t\t  [][][] [][][][][][][]\n\t\t  [][][] [][][][][][][]\n\t\t  [][][] [][][][][][][]\n\t\t  [][][]      \n\t\t  [][][] [][][][][][][]\n\t\t  [][][] [][][][][][][]\n\t\t  [][][] [][][][][][][]\n\n\n\n\n");}

void CantJugadores(int numJugadores, char nombres[2][50]) { //CANTIDAD JUGADORES + NOMBRES
    if (numJugadores == 1) {
        printf("\n Has seleccionado la modalidad de partida en solitario\n\n\tComo te llamas? ");
        scanf("%s", nombres[0]);
    } else if (numJugadores == 2) {
        printf("\n\tCual es el nombre del primer jugador? ");
        scanf("%s", nombres[0]);
        printf("\n\tCual es el nombre del segundo jugador? ");
        scanf("%s", nombres[1]);
        printf("\n\n Han seleccionado la modalidad multijugador.\n\n");
    }
}
int NumeroValido(char *entradaValida) {
    for (int i = 0; i < strlen(entradaValida); i++) {
        if (!isdigit(entradaValida[i])) {
            return 0; // No es un número válido
        }
    }
    return 1; // Número válido
}

void tirar_dados(int dados[], int dadosElegidos[], int nroDados) {
    srand(time(NULL));
    printf("\n\tLanzando dados...\n");
    for (int i = 0; i < nroDados; i++) {
        if (!dadosElegidos[i]) {
            dados[i] = rand() % 6 + 1; // Valores entre 1 y 6
        }
    }
}
void mostrarDados(int dados[]) {
    printf("\n\tDados: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", dados[i]);
    }
    printf("\n");
}

void elegir_dados(int dados[], int dadosElegidos[], int* dadosRestantes) {
    char respuesta[N];
    printf("\n\tSeleccione los dados que desea conservar (ingrese 's' para conservar o 'n' para volver a lanzar):\n");
    for (int i = 0; i < N; i++) {
        printf("Dado %d: %d (s/n)? ", i + 1, dados[i]);
        scanf(" %c", &respuesta[i]);  // Nota el espacio antes del %c para consumir cualquier espacio en blanco
        if (respuesta[i] == 's' || respuesta[i] == 'S') {
            dadosElegidos[i] = 1;
            (*dadosRestantes)--;
        } else {
            dadosElegidos[i] = 0;
        }
    }printf("\n\tDados restantes despues de elegir: %d\n", *dadosRestantes);
}
void mostrarDadosElegidos(int dados[], int dadosElegidos[]) {
    printf("\n\tDados elegidos: ");
    for (int i = 0; i < N; i++) {
        if (dadosElegidos[i]) {
            printf("%d ", dados[i]);
        } else {
            printf("- ");
        }
    }
    printf("\n");
}

void mostrar_opciones_de_puntaje(int jugada[], int puntajeJugador[][2], int jugadorActual) {
    // Ordenar los dados en orden ascendente
    for (int i = 0; i < N; i++) {
        for (int j = 0, h = 1; h < N; j++, h++) {
            if (jugada[j] > jugada[h]) {
                int temp = jugada[h];
                jugada[h] = jugada[j];
                jugada[j] = temp;
            }
        }
    }

    int disponible[N] = {0};
    int registrado[N] = {0};
    int a[11][2] = {0}; // a[i][0] opción, a[i][1]  puntaje

    for (int i = 0; i < N; i++) {
        if (!registrado[i]) {
            for (int j = 0; j < N; j++) {
                if (jugada[i] == jugada[j]) {
                    disponible[i]++;
                    if (i != j) {
                        registrado[j] = 1;
                    }
                }
            }
        }
    }

    for (int i = 0; i < N; i++) {
        if (!registrado[i]) {
            a[jugada[i] - 1][1] = jugada[i] * disponible[i];
            switch (disponible[i]) {
                case 5: puntajeJugador[9][jugadorActual] ? (a[10][1] = 120) : (a[9][1] = 100); break;
                case 4: a[8][1] = 75; break;
                case 3: if (disponible[3] == 2) a[7][1] = 50; break;
                case 2: if (disponible[2] == 3) a[7][1] = 50; break;
            }
        }
    }

    if ((jugada[0] < jugada[1] && jugada[1] < jugada[2] && jugada[2] < jugada[3] && jugada[3] < jugada[4])) a[6][1] = 35;

    printf("\n\n\n");
    printf("\t Opciones disponibles:\n");
    int number = 0;
    int op;
    for (int i = 0; i < 11; i++) {
        if (!puntajeJugador[i][jugadorActual]) {
            if (i < 6) {
                number++;
                a[i][0] = number;
                printf("\n %d) Anotarse: %d al %d \n", a[i][0], a[i][1], i + 1);
            }
            switch (i) {
                case 6: if (a[i][1]) { number++; a[i][0] = number; printf("\n %d) Anotarse: escalera\n", a[i][0]); } else { number++; a[i][0] = number; printf("\n %d) Tacharse: escalera\n", a[i][0]);} break;
                case 7: if (a[i][1]) { number++; a[i][0] = number; printf("\n %d) Anotarse: full\n", a[i][0]); } else { number++; a[i][0] = number; printf("\n %d) Tacharse: full\n", a[i][0]); } break;
                case 8: if (a[i][1]) { number++; a[i][0] = number; printf("\n %d) Anotarse: poker\n", a[i][0]); } else { number++; a[i][0] = number; printf("\n %d) Tacharse: poker\n", a[i][0]); } break;
                case 9: if (a[i][1]) { number++; a[i][0] = number; printf("\n %d) Anotarse: generala\n", a[i][0]); } else { number++; a[i][0] = number; printf("\n %d) Tacharse: generala\n", a[i][0]); } break;
                case 10: if (a[i][1]) { number++; a[i][0] = number; printf("\n %d) Anotarse: doble generala\n", a[i][0]); } else { number++; a[i][0] = number; printf("\n %d) Tacharse: doble generala\n", a[i][0]); } break;
            }
        }
    }

    printf("\n\t Indique el puntaje a guardar: \n");
    scanf("%d", &op);

    // Actualizar el puntaje del jugador solo para la opción elegida
    for (int i = 0; i < NUM_CATEGORIAS; i++) {
        if (op == a[i][0]) {
            puntajeJugador[i][jugadorActual] = a[i][1]; // Asigna el puntaje correspondiente
            break; // Sale del bucle después de actualizar el puntaje
        }
    }
}
int calcular_puntaje_total(int puntajeJugador[][2], int jugador) {
        int total = 0;
        for (int i = 0; i < NUM_CATEGORIAS; i++) {
            if (puntajeJugador[i][jugador] != -1) {
                total += puntajeJugador[i][jugador];
            }
        }
        return total;
    }
void imprimirTablaPuntajes(char nombres[2][50], int puntajes[NUM_CATEGORIAS][2], int numJugadores) {
    const char* categorias[NUM_CATEGORIAS] = {
        "\n1", "2", "3", "4", "5", "6", "Esc", "Full", "Poker", "Grala", "Doble"
    };

    // Imprimir cabecera de la tabla
    printf("\n\nCATEGORIAS\t");
    for (int i = 0; i < numJugadores; i++) {
        printf("%s\t\t", nombres[i]);
    }
    //printf("TOTAL\n");

    // Imprimir puntajes por categoría
    for (int i = 0; i < NUM_CATEGORIAS; i++) {
        printf("%s\t\t", categorias[i]);
        for (int j = 0; j < numJugadores; j++) {
            printf("%d\t\t", puntajes[i][j]);
        }
        printf("\n");
    }

    // Imprimir puntaje total por jugador
    printf("TOTAL\t\t");
    for (int i = 0; i < numJugadores; i++) {
        int total = 0;
        for (int j = 0; j < NUM_CATEGORIAS; j++) {
            total += puntajes[j][i];
        }
        printf("%d\t\t", total);
    }
    printf("\n");
}


    int main(){

    srand(time(NULL));
    int numJugadores;
    char nombres[2][50];
    char entradaValida[10];
    char rtaR;
    int puntajeJugador[NUM_CATEGORIAS][2] = {0};


    introduccion();

    do {
        printf("\n\n\t  ---BIENVENIDO A LA GENERALA DIGITAL---\n\n Cuantos jugadores van a participar? (1 o 2): ");
        scanf("%s", entradaValida); //lee entrada como string
        if (NumeroValido(entradaValida)) {
            numJugadores = atoi(entradaValida); // string a nro por el bug ingresando caracteres en vez de nro
            if (numJugadores != 1 && numJugadores != 2) {
                printf("Por favor, ingrese 1 o 2.\n");
            }
        } else {
            printf("\n\tENTRADA NO VALIDA. Por favor, ingrese 1 o 2.\n");
        }
    } while (numJugadores < 1 || numJugadores > 2);

    CantJugadores(numJugadores, nombres);
    //NOMBRES INGRESADOS
    printf("\n Jugadores registrados:\n");
    for (int i = 0; i < numJugadores; i++) {
        printf("\n -Jugador %d: %s\n", i + 1, nombres[i]);
    }
    //REGLAS
    printf("\n Desea consultar las reglas del juego?. (Responda S para SI/ N para NO)\n\n");
    scanf(" %c", &rtaR); //ESPACIO!!
    if (rtaR == 's' || rtaR == 'S') {
        reglas();
    } else {
        printf("\n\t ...De acuerdo, a JUGAR!\n");
    }
    int turnosPorJugador[2] = {0};

    for (int turno = 0; turno < TURNOS * numJugadores; turno++) {
        int jugadorActual = turno % numJugadores;
        int dados[N] = {0};
        int dadosElegidos[N] = {0};
        int dadosRestantes = N;
        turnosPorJugador[jugadorActual]++;

    printf("\n  %s, es tu turno numero %d \n", nombres[jugadorActual], turnosPorJugador[jugadorActual]); //&turno

        for (int tirada = 0; tirada < 3 && dadosRestantes > 0; tirada++) {
            tirar_dados(dados, dadosElegidos, N);
            mostrarDados(dados);
            if (tirada < 2) {
                elegir_dados(dados, dadosElegidos, &dadosRestantes);
                mostrarDadosElegidos(dados, dadosElegidos);
                mostrarDados(dados);
            }
        }

        // Mostrar opciones de puntaje
        mostrar_opciones_de_puntaje(dados, puntajeJugador, jugadorActual);

        // Imprimir puntajes
        imprimirTablaPuntajes(nombres, puntajeJugador, numJugadores);

}
    //FIN DEL JUEGO
            printf("\n\n\tEl juego ha terminado!\n");
            // Mostrar los puntajes finales y ganador
    int puntajeTotalJugador1 = calcular_puntaje_total(puntajeJugador, 0);
    int puntajeTotalJugador2 = calcular_puntaje_total(puntajeJugador, 1);

    // Determinar el ganador
    if (puntajeTotalJugador1 > puntajeTotalJugador2) {
        printf("\n\tJugador 1 gana!\n");
        printf("\nFELICITACIONES %s !!",nombres[0]);
    } else if (puntajeTotalJugador1 < puntajeTotalJugador2) {
        printf("\n\tJugador 2 gana!\n");
        printf("\nFELICITACIONES %s !!",nombres[1]);
    } else {
        printf("\n\tEs un empate!\n");
        printf("\nBUEN TRABAJO AMIGOS %s !!");
    }


  return 0;
    }
