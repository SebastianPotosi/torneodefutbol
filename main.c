#include <stdio.h>
#include "ingreso.h"
#include "torneo.h"
#include "resultados.h"

int main() {
    ingresarEquipos();
    jugarTorneo();
    mostrarResultados();
    
    return 0;
}
