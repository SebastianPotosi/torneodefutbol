#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "torneo.h"
#include <string.h>

void generarResultadosAleatorios(int numEquipos);
void ingresarResultadosManuales(int numEquipos);

void jugarTorneo() {
    int numEquipos = 0;
    FILE *archivoEquipos = fopen("equipos.txt", "r");
    
    // Cuenta el número de equipos en el archivo
    char equipo[100];
    while (fgets(equipo, sizeof(equipo), archivoEquipos) != NULL) {
        numEquipos++;
    }
    fclose(archivoEquipos);
    
    // Pregunta al usuario de que modo quiere ingresar los resultados
    char opcion;
    printf("\nDesea ingresar manualmente los resultados (m) o generarlos automaticamente (a)? ");
    scanf(" %c", &opcion);
    
    if (opcion == 'm' || opcion == 'M') {
        ingresarResultadosManuales(numEquipos);
    } else if (opcion == 'a' || opcion == 'A') {
        generarResultadosAleatorios(numEquipos);
    } else {
        printf("Opcion invalida. Saliendo del programa.\n");
        exit(1);
    }
}

void generarResultadosAleatorios(int numEquipos) {
    srand(time(NULL));
    
    FILE *archivoResultados = fopen("resultados.txt", "w");
    
    FILE *archivoEquipos = fopen("equipos.txt", "r");
    char equipos[numEquipos][100];
    
    for (int i = 0; i < numEquipos; i++) {
        fgets(equipos[i], sizeof(equipos[i]), archivoEquipos);
        equipos[i][strlen(equipos[i]) - 1] = '\0'; // Elimina el salto de línea
    }
    fclose(archivoEquipos);
    
    for (int i = 0; i < numEquipos; i++) {
        for (int j = i + 1; j < numEquipos; j++) {
            int golesEquipo1 = rand() % 5;
            int golesEquipo2 = rand() % 5;
            
            fprintf(archivoResultados, "%s,%s,%d,%d\n", equipos[i], equipos[j], golesEquipo1, golesEquipo2);
        }
    }
    
    fclose(archivoResultados);
}

void ingresarResultadosManuales(int numEquipos) {
    FILE *archivoResultados = fopen("resultados.txt", "w");
    
    FILE *archivoEquipos = fopen("equipos.txt", "r");
    char equipos[numEquipos][100];
    
    for (int i = 0; i < numEquipos; i++) {
        fgets(equipos[i], sizeof(equipos[i]), archivoEquipos);
        equipos[i][strlen(equipos[i]) - 1] = '\0'; // Elimina el salto de línea
    }
    fclose(archivoEquipos);
    
    for (int i = 0; i < numEquipos; i++) {
        for (int j = i + 1; j < numEquipos; j++) {
            int golesEquipo1, golesEquipo2;
            
            printf("Ingrese los goles para el partido entre %s y %s:\n", equipos[i], equipos[j]);
            printf("%s: ", equipos[i]);
            scanf("%d", &golesEquipo1);
            
            printf("%s: ", equipos[j]);
            scanf("%d", &golesEquipo2);
            
            fprintf(archivoResultados, "%s,%s,%d,%d\n", equipos[i], equipos[j], golesEquipo1, golesEquipo2);
        }
    }
    
    fclose(archivoResultados);
}
