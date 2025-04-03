
#include <stdio.h>
#include "read_file.h"
#include "folder.h"
#include "functions.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Uso: ./app1 metrica1 metrica2 ... metrican\n");
        return 1;
    }

    funcion_t funciones[] = {pms, pls, dms, dls, dmsp, dlsp, apo, apd, ims, hp};
    char *metricas[] = {"pms", "pls", "dms", "dls", "dmsp", "dlsp", "apo", "apd", "ims", "hp"};
    int nro_metricas = sizeof(metricas) / sizeof(metricas[0]);

    cvs_table table = read_file("pizzas_orders.csv");
    show_table(table);
    // Recorrer los argumentos y llamar a las funciones dinámicamente
    for (int i = 1; i < argc; i++) {
        for (int j = 0; j < nro_metricas; j++) {
            if (strcmp(argv[i], metricas[j]) == 0) {
                printf("Llamando a la función %s\n", metricas[j]);
                funciones[j](&table);  // Llamada dinámica a la función usando puntero
                break;
            }
        }
    }
    free_table(table);
    return 0;
}
