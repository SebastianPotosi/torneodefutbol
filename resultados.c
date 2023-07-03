#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char equipo1[100];
    char equipo2[100];
    int golesEquipo1;
    int golesEquipo2;
} Partido;

void cargarResultados(Partido *partidos, int numPartidos);
int calcularPuntos(char equipo[100], Partido *partidos, int numPartidos);
void ordenarEquipos(char equipos[][100], int puntos[], int numEquipos);

void mostrarResultados() {
    FILE *archivoResultados = fopen("resultados.txt", "r");
    
    int numPartidos = 0;
    char linea[400];
    while (fgets(linea, sizeof(linea), archivoResultados) != NULL) {
        numPartidos++;
    }
    rewind(archivoResultados);
    
    Partido *partidos = malloc(numPartidos * sizeof(Partido));
    
    int i = 0;
    while (fgets(linea, sizeof(linea), archivoResultados) != NULL) {
        sscanf(linea, "%[^,],%[^,],%d,%d", partidos[i].equipo1, partidos[i].equipo2,
               &partidos[i].golesEquipo1, &partidos[i].golesEquipo2);
        i++;
    }
    
    fclose(archivoResultados);
    
    printf("\nTabla de resultados:\n");
    for (int i = 0; i < numPartidos; i++) {
        printf("%s %d - %d %s\n", partidos[i].equipo1, partidos[i].golesEquipo1,
               partidos[i].golesEquipo2, partidos[i].equipo2);
    }
    
    printf("\nTabla de posiciones:\n");
    FILE *archivoEquipos = fopen("equipos.txt", "r");
    char equipos[numPartidos][100];
    
    for (int i = 0; i < numPartidos; i++) {
        fgets(equipos[i], sizeof(equipos[i]), archivoEquipos);
        equipos[i][strcspn(equipos[i], "\n")] = '\0'; //elimina el salto de linea
    }
    rewind (archivoEquipos);
    
    fclose(archivoEquipos);
    
    int puntos[numPartidos];
    for (int i = 0; i < numPartidos; i++) {
        puntos[i] = calcularPuntos(equipos[i], partidos, numPartidos);
    }
    
    ordenarEquipos(equipos, puntos, numPartidos);
    
    for (int i = 0; i < numPartidos; i++) {
        printf("%s: %d puntos\n", equipos[i], puntos[i]);
    }
    
    free(partidos);
}

int calcularPuntos(char equipo[100], Partido *partidos, int numPartidos) {
    int puntos = 0;
    
    for (int i = 0; i < numPartidos; i++) {
        if (strcmp(equipo, partidos[i].equipo1) == 0) {
            if (partidos[i].golesEquipo1 > partidos[i].golesEquipo2) {
                puntos += 3; // Es una victoria
            } else if (partidos[i].golesEquipo1 == partidos[i].golesEquipo2) {
                puntos += 1; // Es un empate
            }
        } else if (strcmp(equipo, partidos[i].equipo2) == 0) {
            if (partidos[i].golesEquipo2 > partidos[i].golesEquipo1) {
                puntos += 3; // Es una victoria
            } else if (partidos[i].golesEquipo2 == partidos[i].golesEquipo1) {
                puntos += 1; // Es un empate
            }
        }
    }
    
    return puntos;
}

void ordenarEquipos(char equipos[][100], int puntos[], int numEquipos) {
    for (int i = 0; i < numEquipos - 1; i++) {
        for (int j = 0; j < numEquipos - i - 1; j++) {
            if (puntos[j] < puntos[j + 1]) {
                int tempPuntos = puntos[j];
                puntos[j] = puntos[j + 1];
                puntos[j + 1] = tempPuntos;
                
                char tempEquipo[100];
                strcpy(tempEquipo, equipos[j]);
                strcpy(equipos[j], equipos[j + 1]);
                strcpy(equipos[j + 1], tempEquipo);
            }
        }
    }
}
