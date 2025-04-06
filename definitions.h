#include <stdio.h>
typedef void (*funcion_t)(FILE*, int);
#define MAX_LINE_LENGTH 1024
#define MAX_FIELDS 12
#define MAX_FIELD_LENGTH 256



char* extract_field(const char* input, int* offset);
char * get_field(const char* input, int field_idx);
