#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Agrega o actualiza la clave en la lista de contadores
 */
r_counter_list *counter_add_or_update(r_counter_list *counter, char *key, float value)
{
    if (counter == NULL)
    {
        counter = (r_counter_list *)malloc(sizeof(r_counter_list));
        counter->data = (r_counter **)malloc(sizeof(r_counter *));
        counter->size = 0;
    }
    // lo encuentra y suma
    r_counter *get = counter_get(counter, key);
    if (get != NULL)
    {
        get->value += value;
        return counter;
    }
    // no lo encuentra y lo agrega
    counter->data = (r_counter **)realloc(counter->data, sizeof(r_counter *) * (counter->size + 1));
    r_counter *new_counter = (r_counter *)malloc(sizeof(r_counter));
    new_counter->key = key;
    new_counter->value = value;
    counter->data[counter->size] = new_counter;
    counter->size++;
    return counter;
}
/**
 * Obtiene un contador por su llave
 */
r_counter *counter_get(r_counter_list *counter, char *key)
{
    for (int i = 0; i < counter->size; i++)
    {
        if (strcmp(counter->data[i]->key, key) == 0)
        {
            return counter->data[i];
        }
    }
    return NULL;
}
/**
 * Imprime la lista de contadores
 */
void counter_print(r_counter_list *counter)
{
    printf("Contadores: %d\n", counter->size);
    for (int i = 0; i < counter->size; i++)
    {
        printf("%s: %f\n", counter->data[i]->key, counter->data[i]->value);
    }
}
/**
 * Libera la memoria de la lista de contadores
 */
void counter_free(r_counter_list *counter)
{
    for (int i = 0; i < counter->size; i++)
    {
        free(counter->data[i]);
    }
    free(counter->data);
    free(counter);
}
/**
 * Ordena la lista de contadores de mayor a menor
 */
void counter_sort(r_counter_list *counter)
{
    for (int i = 0; i < counter->size; i++)
    {
        for (int j = i + 1; j < counter->size; j++)
        {
            if (counter->data[i]->value < counter->data[j]->value)
            {
                r_counter *temp = counter->data[i];
                counter->data[i] = counter->data[j];
                counter->data[j] = temp;
            }
        }
    }
}

void counter_max(r_counter_list *counter)
{
    if (counter == NULL || counter->size == 0)
    {
        return NULL;
    }
    r_counter *temp = counter->data[0];
    for (int n = 0; n < counter->size; n++)
    {
        if (counter->data[n]->value > temp->value)
        {
            temp = counter->data[n];
        }
    }
    return temp;
}

void counter_min(r_counter_list *counter)
{
    if (counter == NULL || counter->size == 0)
    {
        return NULL;
    }
    r_counter *temp = counter->data[0];
    for (int n = 0; n < counter->size; n++)
    {
        if (counter->data[n]->value < temp->value)
        {
            temp = counter->data[n];
        }
    }
    return temp;
}