#include "definitions.h"
#include "pls.h"
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ims(FILE *file, int lines) {
  char *keys[lines];
  float values[lines];
  int count = 0;

  char line[MAX_LINE_LENGTH];
  fgets(line, MAX_LINE_LENGTH, file); // Saltar encabezados

  while (fgets(line, MAX_LINE_LENGTH, file)) {

    char *pizza_ingredients = get_field(line, 10);
    printf("ingredientes %s \n", pizza_ingredients);
    float quantity = atof(get_field(line, 3));
    // vamos a separar los ingredientes por comas
    char *ingredient = strtok(pizza_ingredients, ",");

    while (ingredient != NULL) {
      // Buscamos el ingrediente en la lista de ingredientes
      printf("ingredientes %s  [%s]\n", pizza_ingredients, ingredient);
      int idx = -1;
      for (int n = 0; n < count; n++) {
        if (strcmp(keys[n], ingredient) == 0) {
          values[n] += quantity;
          idx = n;
          break;
        }
      }
      if (idx == -1) {
        keys[count] = strdup(ingredient);
        values[count] = quantity;
        count++;
      }
      ingredient = strtok(NULL, ",");
    }
  }

  if (count > 0) {

    // Buscamos el máximo
    float max = FLT_MIN;
    int max_index = -1;
    for (int n = 0; n < count; n++) {
      if (values[n] > max) {
        max = values[n];
        max_index = n;
      }
    }
    printf("\nEl ingrediente más vendido es %s con una cantidad de %3.1f\n",
           keys[max_index], values[max_index]);
  } else {
    printf("\nNo se encontraron pizzas en el archivo.\n");
  }
  rewind(file); // Volver al inicio para otra función
}