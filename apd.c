#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pls.h"
#include <float.h>

void apd(FILE *file, int lines)
{
    char *keys[lines];
    float values[lines];
    float counts[lines];
    int count = 0;

    char line[min_LINE_LENGTH];
    fgets(line, min_LINE_LENGTH, file); // Saltar encabezados

    while (fgets(line, min_LINE_LENGTH, file))
    {
        char *tokens[12];
        int i = 0, inside_quotes = 0;
        char *token = strtok(line, ",");

        while (token != NULL && i < 12)
        {
            if (inside_quotes)
            {
                strcat(tokens[i - 1], ",");
                strcat(tokens[i - 1], token);
                if (token[strlen(token) - 1] == '"')
                {
                    inside_quotes = 0;
                }
            }
            else
            {
                tokens[i++] = token;
                if (token[0] == '"' && token[strlen(token) - 1] != '"')
                {
                    inside_quotes = 1;
                }
            }
            token = strtok(NULL, ",");
        }

        if (i >= 12)
        {
            char *pizza_date = tokens[4];
            float quantity = atof(tokens[3]);
            // Debo buscar en la lista para saber si ya existe

            int idx = -1;
            for (int n = 0; n < count; n++)
            {
                if (strcmp(keys[n], pizza_date) == 0)
                {
                    values[n] = values[n] + quantity;
                    counts[count]++; // counts[count] = counts[count]+1;
                    idx = n;
                    break;
                }
            }
            if (idx == -1)
            {
                keys[count] = strdup(pizza_date);
                values[count] = quantity;
                counts[count] = 1;
                count++;
            }
        }
    }

    if (count > 0)
    {
        for (int n = 0; n < count; n++)
        {

            printf("\nEl promedio de la fecha %s es de %3.1f\n", keys[n], values[n] / counts[n]);
        }
    }
    else
    {
        printf("\nNo se encontraron pizzas en el archivo.\n");
    }
    rewind(file); // Volver al inicio para otra función
}