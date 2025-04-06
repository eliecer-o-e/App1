#include "pls.h"
#include "definitions.h"
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void pls(FILE *file, int lines) {

  char *keys[lines];
  float values[lines];
  int count = 0;

  char line[MAX_LINE_LENGTH];
  fgets(line, MAX_LINE_LENGTH, file); // Saltar encabezados

  while (fgets(line, MAX_LINE_LENGTH, file)) {
      char *pizza_name = get_field(line, 2);     // Tercera columna (pizza_name_id)
      float quantity = atof(get_field(line, 3)); // Cuarta columna (quantity)
      // Debo buscar en la lista para saber si ya existe
      int idx = -1;
      for (int n = 0; n < count; n++) {
        if (strcmp(keys[n], pizza_name) == 0) {
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
    }

  if (count > 0) {

    // Buscamos el máximo
    float min = FLT_MAX;
    int min_index = -1;
    for (int n = 0; n < count; n++) {
      if (values[n] < min) {
        min = values[n];
        min_index = n;
      }
    }
    printf("\nLa pizza menos vendida es %s con una cantidad de %3.1f\n",
           keys[min_index], values[min_index]);
  } else {
    printf("\nNo se encontraron pizzas en el archivo.\n");
  }
  rewind(file); // Volver al inicio para otra función
}