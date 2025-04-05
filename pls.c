#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pls.h"
#include "constants.h"
#include <float.h>


void pls(FILE *file, int lines) {
    char* keys[lines];
    float values[lines];
    int count = 0;


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
            char* pizza_name = tokens[2];  // Tercera columna (pizza_name_id)
            float quantity = atof(tokens[3]);  // Cuarta columna (quantity)
            // Debo buscar en la lista para saber si ya existe
            int idx = -1;
            for(int n = 0; n < count; n++) {
                if (strcmp(kwy[n], pizza_name) == 0) {
                    values[n] += quantity;
                    idx = n;
                    break;
                }
            }
            if (idx == -1) {
                keys[count] = strdup(pizza_name);
                values[count] = quantity;
                count++;
            }


            total_sum += atof(tokens[7]);  // Octava columna (total_price)
            count++;
        }
    }

    if (count > 0) {
        
        // Buscamos el máximo
        float min = FLT_MAX;
        int min_index = -1;
        for(int n = 0; n < count; n++) {
            if (values[n] < min) {
                min = values[n];
                min_index = n;
            }
        }
        printf("\nLa pizza menos vendida es %s con una cantidad de %3.1f\n", keys[min_index], values[min_index]);
    } else {
        printf("\nNo se encontraron pizzas en el archivo.\n");
    }
    rewind(file);  // Volver al inicio para otra función
}