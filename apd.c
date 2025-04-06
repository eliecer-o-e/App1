#include "definitions.h"
#include "pls.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void apd(FILE *file, int lines) {
  char *keys[lines];
  float values[lines];
  float counts[lines];
  int count = 0;

  char line[MAX_LINE_LENGTH];
  fgets(line, MAX_LINE_LENGTH, file); // Saltar encabezados

  while (fgets(line, MAX_LINE_LENGTH, file)) {

      char *pizza_date = get_field(line, 4); 
      float quantity = atof(get_field(line, 3) );
      // Debo buscar en la lista para saber si ya existe

      int idx = -1;
      for (int n = 0; n < count; n++) {
        if (strcmp(keys[n], pizza_date) == 0) {
          values[n] = values[n] + quantity;
          counts[n] = counts[n] + 1;
          idx = n;
          break;
        }
      }
      if (idx == -1) {
        keys[count] = strdup(pizza_date);
        values[count] = quantity;
        counts[count] = 1;
        count++;
      }
  }

  if (count > 0) {
    for (int n = 0; n < count; n++) {

      printf("\nEl promedio de la fecha %s es de %3.1f %f\n", keys[n],
             (values[n] / counts[n]), counts[n]);
    }
  } else {
    printf("\nNo se encontraron pizzas en el archivo.\n");
  }
  rewind(file); // Volver al inicio para otra función

}