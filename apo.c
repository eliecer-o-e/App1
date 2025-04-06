#include <stdio.h>
#include <stdlib.h>
#include "pls.h"
#include "definitions.h"


void apo(FILE *file, int lines) {
    int count = 0;
    float total = 0;

    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, file);  // Saltar encabezados

    while (fgets(line, MAX_LINE_LENGTH, file)) {

            float quantity = atof(get_field(line, 3));  
            total+= quantity;  // Acumular el total de dinero
                count++;
    }

    if (count > 0) {
        float average = total / count;  // Calcular el promedio
        printf("\nEl promedio de pizzas por orden es %3.1f\n", average);
    } else {
        printf("\nNo se encontraron pizzas en el archivo.\n");
    }
    rewind(file);  // Volver al inicio para otra función
}