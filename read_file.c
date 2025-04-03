//
//  read_file.c
//  tarea
//
//  Created by Eliecer Osorio on 27-03-25.
//
#include "read_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 Dada la entrada de char* y un offset obtiene el siguiente campo que es aquel que se encuentra antes de la coma (,)
 
 Para el caso que el campo se encuentra entre comillas, va a omitir las comas que se encuentran dentro y lo interpreta como un solo valor.
 */
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

void show(cvs_row row) {
    printf("%3.1f, %3.1f, %s, %3.1f, %s, %s, %3.1f, %3.1f, %c, %s, <%s>, %s",
           row.pizza_id, row.order_id, row.pizza_name_id, row.quantity, row.order_date, row.order_time, row.unit_price, row.total_price, row.pizza_size, row.pizza_category, row.pizza_ingredients, row.pizza_name);
}

void show_table(cvs_table table)
{
    printf("\n");
    for(int n = 0; n < table.count; n++)
    {
        show(*table.data[n]);
    }
    printf("\n");
}


void free_row(cvs_row* row) {
    free(row->pizza_name_id);
    free(row->order_date);
    free(row->order_time);
    free(row->pizza_category);
    free(row->pizza_ingredients);
    free(row->pizza_name);
    free(row);
}

void free_table(cvs_table table) {
    // Liberar memoria
    for (int i = 0; i < table.count; ++i) {
        free_row(table.data[i]);
    }
    free(table.data);
}
/**
 En esta función se leen todos los campos de una fila.
 Se crea la estructura cvs_row y se llena con los valores de los campos.
 
 Se asume que vienen los 12 campos.
 */
cvs_row* read_line(char* line) {
    char* value;
    int offset = 0;
    
    cvs_row* reg = malloc(sizeof(cvs_row));
    
    value = extract_field(line, &offset);
    (*reg).pizza_id = atof(value);
    value = extract_field(line, &offset);
    (*reg).order_id = atof(value);
    value = extract_field(line, &offset);
    (*reg).pizza_name_id = value;
    value = extract_field(line, &offset);
    (*reg).quantity = atof(value);
    value = extract_field(line, &offset);
    (*reg).order_date = value;
    value = extract_field(line, &offset);
    (*reg).order_time = value;
    value = extract_field(line, &offset);
    (*reg).unit_price = atof(value);
    value = extract_field(line, &offset);
    (*reg).total_price = atof(value);
    value = extract_field(line, &offset);
    (*reg).pizza_size = *value;
    value = extract_field(line, &offset);
    (*reg).pizza_category = value;
    value = extract_field(line, &offset);
    (*reg).pizza_ingredients = value;
    value = extract_field(line, &offset);
    (*reg).pizza_name = value;
    return reg;
    
}

/**
 Recibe de parámetro el nombre del archivo.
 Lo lee y retorna una estructura definida por cvs_table
 */
cvs_table read_file(const char* filename) {
    cvs_table table;
    table.data = NULL;
    table.count = 0;
    table.capacity = 0;
    
    // Puntero al archivo
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("No se pudo abrir el archivo");
        return table;
    }
    
    // rows es un puntero a punteros
    cvs_row** rows = NULL;
    int capacity = 10;
    int count = 0;
    
    // crea un arreglo que va a apuntar los punteros del arreglo de filas
    rows = malloc(capacity * sizeof(cvs_row*));
    
    if(!rows) {
        fclose(file);
        return table;
    }
    
    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, file);  // Saltar encabezados
    
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        
        // Redimensionar rows si es necesario
        if (count >= capacity) {
            capacity *= 2;
            cvs_row** temp = realloc(rows, capacity * sizeof(cvs_row*));
            if (!temp) {
                for (int i = 0; i < count; i++) {
                    free(rows[i]);
                }
                free(rows);
                fclose(file);
                return table;
            }
            rows = temp;
        }
        
        // se crea puntero a la fila
        cvs_row* row = read_line(line);
        if (!row) continue;
        
        rows[count++] = row;
    }
    fclose(file);
    table.count = count;
    table.capacity = capacity;
    table.data = rows;
    
    return table;
}

