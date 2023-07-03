#ifndef RESULTADOS_H
#define RESULTADOS_H

typedef struct {
    char equipo1[100];
    char equipo2[100];
    int golesEquipo1;
    int golesEquipo2;
} Partido;

void mostrarResultados();

#endif  // RESULTADOS_H
