#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pls.h"
#include "constants.h"
#include <float.h>


void hp(FILE *file, int lines) {
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
            char* pizza_date = tokens[9];  
            float money = atof(tokens[3]);  
            // Debo buscar en la lista para saber si ya existe

            int idx = -1;
            for(int n = 0; n < count; n++) {
                if (strcmp(keys[n], pizza_date) == 0) {
                    values[n] += money;
                    idx = n;
                    break;
                }
            }
            if (idx == -1) {
                keys[count] = strdup(pizza_date);
                values[count] = money;
                count++;
            }
            count++;
        }
    }

    if (count > 0) {
     for(int i = 0; i < count; i++) {
            printf("cantidad de pizas de la categoria %s es  %3.1f\n", keys[i], values[i]);
        }   
     
    } else {
        printf("\nNo se encontraron pizzas en el archivo.\n");
    }
    rewind(file);  // Volver al inicio para otra función
}