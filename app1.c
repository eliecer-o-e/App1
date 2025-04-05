
#include <stdio.h>
#include "pms.h"
#include "pls.h"
#include "dms.h"
#include "dls.h"
#include "dmsp.h"
#include "dlsp.h"
#include "apo.h"
#include "apd.h"
#include "ims.h"
#include "hp.h"

int rows_numbers(FILE* file)
{
    char line[MAX_LINE_LENGTH];
    int count = 0;
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL)
    {
        count++;
    }
    rewind(file); // Regresar al inicio del archivo
    return --count;
}

int main(int argc, char *argv[]){



    if (argc < 3)
    {
        printf("Uso: ./app1 archivo.csv metrica1 metrica2 ... metrican\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Error al abrir el archivo %s\n", argv[1]);
        return 1;
    }

    int numerolineas = rows_numbers(file);

    funcion_t funciones[] = {pms, pls, dms, dls, dmsp, dlsp, apo, apd, ims, hp};
    char *metricas[] = {"pms", "pls", "dms", "dls", "dmsp", "dlsp", "apo", "apd", "ims", "hp"};
    int nro_metricas = sizeof(metricas) / sizeof(metricas[0]);

    for(int n = 2; n < argc; n++)
    {
        char* function = argv[n];
        for(int i = 0; i < metricas; i++)
        {
            if (strcmp(function, metricas[i]) == 0)
            {
                printf("Ejecutando %s...\n", function);
                funciones[i](file, numerolineas);
                break;
            }
        }
            
    }
    return 0;
}
