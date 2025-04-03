#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_file.h"

typedef void (*funcion_t)(cvs_table*);

void pms(cvs_table* table);
void pls(cvs_table* table);
void dms(cvs_table* table);
void dls(cvs_table* table);
void dmsp(cvs_table* table);
void dlsp(cvs_table* table);
void apo(cvs_table* table);
void apd(cvs_table* table);
void ims(cvs_table* table);
void hp(cvs_table* table);



#endif // FUNCTIONS_H