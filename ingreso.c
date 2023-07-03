#include <stdio.h>
#include <string.h>
#include "ingreso.h"
#include "torneo.h"

void ingresarEquipos() {
    FILE *archivoEquipos = fopen("equipos.txt", "w");
    char equipo[100];
    
    printf("Ingrese los nombres de los equipos en singular para evitar inconvenientes (ingrese 'terminar' para finalizar):\n");
    while (1) {
        printf("Equipo: ");
        scanf("%s", equipo);
        
        if (strcmp(equipo, "terminar") == 0) {
            break;
        }
        
        fprintf(archivoEquipos, "%s\n", equipo);
    }
    
    fclose(archivoEquipos);
}
