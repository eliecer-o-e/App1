#include "definitions.h"
#include "pls.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hp(FILE *file, int lines) {
  char *keys[lines];
  float values[lines];
  int count = 0;

  char line[MAX_LINE_LENGTH];
  fgets(line, MAX_LINE_LENGTH, file); // Saltar encabezados

  while (fgets(line, MAX_LINE_LENGTH, file)) {
    
      char *pizza_date = get_field(line, 9);
      float money = atof(get_field(line,3));
      // Debo buscar en la lista para saber si ya existe

      int idx = -1;
      for (int n = 0; n < count; n++) {
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
  }

  if (count > 0) {
    for (int i = 0; i < count; i++) {
      printf("\nCantidad de pizas vendidas de la categoria %s es  %3.1f\n", keys[i],
             values[i]);
    }

  } else {
    printf("\nNo se encontraron pizzas en el archivo.\n");
  }
  rewind(file); // Volver al inicio para otra función

}