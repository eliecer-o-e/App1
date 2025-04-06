#include "definitions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* extract_field(const char* input, int* offset) {
    int i = *offset;
    int buffer_size = 128;
    char* buffer = malloc(buffer_size);
    int len = 0;
    int in_quotes = 0;
    
    if (input[i] == '"') {
        in_quotes = 1;
        i++;
    }
    
    while(input[i])
    {
        if(in_quotes) {
            if(input[i] == '"') {
                i++;
                in_quotes = 0;
            }
            else {
                buffer[len++] = input[i];
                i++;
            }
        }
        else if(input[i] == ',') {
            i++;
            break;
        }
        else {
            buffer[len++] = input[i];
            i++;
        }
        if (len >= buffer_size - 1) {
            buffer_size *= 2;
            buffer = realloc(buffer, buffer_size);
        }
    }
    // Se acabó la línea o se encontró una ,
    buffer[len] = '\0';
    *offset = i;
    return buffer;
    
}
char*  get_field(const char* input, int field_idx) {
    int offset = 0;
    char* value = NULL;
    for(int n = 0; n<= field_idx; n++) {
        value = extract_field(input, &offset);
    }
    return value;
}