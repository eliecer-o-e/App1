#include "functions.h"
#include "util.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
    Pizza más vendida
*/
void pms(cvs_table* table){

    r_counter_list* counter = NULL;
    for(int n = 0; n < table->count; n++) {
        char* pizza = table->data[n]->pizza_name_id;
        float value = table->data[n]->quantity;
        counter = counter_add_or_update(counter, pizza, value);  
    }
    counter_sort(counter);
    r_counter* mayor = counter->data[0];
    char* pizza = mayor->key;
    float value = mayor->value;
    printf("La pizza más vendida es %s con una cantidad de %3.1f\n", pizza, value);
}
/*
    Pizza menos vendida
*/
void pls(cvs_table* table){

}
/*
    Fecha con más ventas en términos de dinero (junto a la cantidad de dinero recaudado)
*/
void dms(cvs_table* table){

}
/*
    Fecha con menos ventas en términos de dinero (junto a la cantidad de dinero recaudado)
*/
void dls(cvs_table* table){

}
/*
    Fecha con más ventas en términos de cantidad de pizzas (junto a la cantidad de pizzas)
*/
void dmsp(cvs_table* table){

}
/*
    Fecha con menos ventas en términos de cantidad de pizzas (junto a la cantidad de pizzas)
*/
void dlsp(cvs_table* table){

}
/*
    Promedio de pizzas por orden
*/
void apo(cvs_table* table){

}
/*
    Promedio de pizzas por día
*/
void apd(cvs_table* table){

}
/*
    Ingrediente más vendido
*/
void ims(cvs_table* table){

}
/*
    Cantidad de pizzas por categoría vendidas
*/
void hp(cvs_table* table){
    r_counter_list* counter = NULL;

    for(int n = 0; n < table->count; n++) {
        float value = table->data[n]->quantity;
        char* ingredients = table->data[n]->pizza_ingredients;

        // Ya que strtok modifica la cadena original, se crea una copia de la cadena
        size_t len = strlen(ingredients);
        char* copyIngredients = malloc(len + 1);
        strcpy(copyIngredients, ingredients);
        // se separa la cadena por comas (strtok coloca un \0 en cada coma)
        char* ingredient = strtok(copyIngredients, ",");
        while (ingredient != NULL) {
            counter = counter_add_or_update(counter, ingredient, value);
            ingredient = strtok(NULL, ",");
        }
    }
    counter_sort(counter);
    r_counter* mayor = counter->data[0];
    char* ingr = mayor->key;
    float value = mayor->value;
    printf("El ingrediente más vendido es %s con una cantidad de %3.1f\n", ingr, value);
}
