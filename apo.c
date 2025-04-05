#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pls.h"
#include "constants.h"
#include <float.h>


void apo(FILE *file, int lines) {
    int count = 0;
    int total = 0;

    char line[min_LINE_LENGTH];
    fgets(line, min_LINE_LENGTH, file);  // Saltar encabezados

    while (fgets(line, min_LINE_LENGTH, file)) {
        char *tokens[12];
        int i = 0, inside_quotes = 0;
        char *token = strtok(line, ",");

        while (token != NULL && i < 12) {
            if (inside_quotes) {
                strcat(tokens[i - 1], ",");
                strcat(tokens[i - 1], token);
                if (token[strlen(token) - 1] == '"') {
                    inside_quotes = 0;
                }
            } else {
                tokens[i++] = token;
                if (token[0] == '"' && token[strlen(token) - 1] != '"') {
                    inside_quotes = 1;
                }
            }
            token = strtok(NULL, ",");
        }

        if (i >= 12) {
            float quantity = atof(tokens[3]);  
            total+= quantity;  // Acumular el total de dinero
                count++;
        }
    }

    if (count > 0) {
        float average = total / count;  // Calcular el promedio
        printf("\nEl promedio de pizzas por orden es %3.1f\n", average);
    } else {
        printf("\nNo se encontraron pizzas en el archivo.\n");
    }
    rewind(file);  // Volver al inicio para otra función
}