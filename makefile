# Nombre del compilador
CC = gcc

# Flags de compilación: -Wall (warnings), -g (debug)
CFLAGS = -Wall -g

# Carpetas
SRC_DIR = .
BUILD_DIR = build
BIN_DIR = bin

# Archivos fuente
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Archivos objeto (reemplaza .c por .o)
OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(SRCS)))

# Nombre del ejecutable
TARGET = $(BIN_DIR)/app

# Regla por defecto
all:	$(TARGET)

# Regla para compilar el ejecutable
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)


# Compilar cada .c a su .o correspondiente
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


# Crear carpetas si no existen
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)
	
# Limpiar archivos generados
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
