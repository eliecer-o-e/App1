#ifndef READ_FILE_H
#define READ_FILE_H


#define MAX_LINE_LENGTH 1024

// Estructura del archivo cvs
typedef struct {
    float pizza_id;
    float order_id;
    char* pizza_name_id;
    float quantity;
    char* order_date;
    char* order_time;
    float unit_price;
    float total_price;
    char pizza_size;
    char* pizza_category;
    char* pizza_ingredients;
    char* pizza_name;
} cvs_row;

typedef struct {
    cvs_row** data;
    int count;
    int capacity;
} cvs_table;


// Lee el contenido completo de un archivo CSV y lo retorna como un string.
// El caller debe liberar la memoria retornada.
cvs_table read_file(const char* filename);
void show_table(cvs_table table);
void free_table(cvs_table table);
#endif // READ_FILE_H
