//
//  folder.c
//  tarea
//
//  Created by Eliecer Osorio on 29-03-25.
//
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>


char* get_current_folder(void) {
    char temp[PATH_MAX];
    if (getcwd(temp, sizeof(temp)) == NULL) {
        return NULL;
    }

    // Copiar a memoria dinámica.
    char* result = malloc(strlen(temp) + 1);
    if (result != NULL) {
        strcpy(result, temp);
    }
    return result;
}
