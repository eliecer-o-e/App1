#ifndef UTIL_H
#define UTIL_H

/** esta estructura va a servir para contar los elementos */
typedef struct {
    char* key; // representa lo que se busca (fecha, nombre pizza)
    float value; // lleva la cuenta o la suma de lo que se busca
} r_counter;

/**
 * Estructura que contiene la lista de contadores
 */
typedef struct {
    r_counter** data;
    int size;
} r_counter_list;

r_counter_list* counter_add_or_update(r_counter_list* counter, char* key, float value);
r_counter* counter_get(r_counter_list* counter, char* key);
void counter_print(r_counter_list* counter);
void counter_free(r_counter_list* counter);
void counter_sort(r_counter_list* counter);

#endif // UTIL_H