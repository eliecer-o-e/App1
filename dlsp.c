#include "definitions.h"
#include "pls.h"
#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dlsp(FILE *file, int lines) {
  char *keys[lines];
  float values[lines];
  int count = 0;

  char line[MAX_LINE_LENGTH];
  fgets(line, MAX_LINE_LENGTH, file); // Saltar encabezados

  while (fgets(line, MAX_LINE_LENGTH, file)) {
    char *pizza_date = get_field(line, 4); // Tercera columna (pizza_name_id)
    float quantity = atof(get_field(line, 3)); // Cuarta columna (quantity)
    // Debo buscar en la lista para saber si ya existe

    int idx = -1;
    for (int n = 0; n < count; n++) {
      if (strcmp(keys[n], pizza_date) == 0) {
        values[n] += quantity;
        idx = n;
        break;
      }
    }
    if (idx == -1) {
      keys[count] = strdup(pizza_date);
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
    printf("\nLa fecha con menos ventas %s con una cantidad de %3.1f\n",
           keys[min_index], values[min_index]);
  } else {
    printf("\nNo se encontraron pizzas en el archivo.\n");
  }
  rewind(file); // Volver al inicio para otra función

}