# Variables
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
TARGET = app-cliente
OBJS = app-cliente.o claves.o

# Compilar el ejecutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compilar app-cliente.c
app-cliente.o: src/app-cliente.c src/claves.h
	$(CC) $(CFLAGS) -c src/app-cliente.c

# Compilar claves.c
claves.o: src/claves.c src/claves.h
	$(CC) $(CFLAGS) -c src/claves.c

# Limpiar archivos intermedios
clean:
	rm -f $(OBJS) $(TARGET)

# Recompilar desde cero
rebuild: clean $(TARGET)

# Reglas por defecto
.PHONY: all clean rebuild
