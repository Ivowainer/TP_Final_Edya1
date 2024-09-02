# Variables
CC = gcc
CFLAGS = -I./structures -I./dstar_lite
LDFLAGS = -lm
SRC_DIR = .
STRUCTURES_DIR = ./structures
DSTAR_DIR = ./dstar_lite

TEMP_DIR = ./temp

# Archivos fuente
SRC = $(SRC_DIR)/main.c \
	  $(STRUCTURES_DIR)/bheap/bheap.c \
	  $(STRUCTURES_DIR)/node/node.c \
	  $(STRUCTURES_DIR)/list/clist.c \
	  $(DSTAR_DIR)/dstar_lite.c \

# Archivos objeto
OBJ = $(SRC:.c=.o)

# Ejecutable
TARGET = robot

# Reglas
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

clean_objs:
	rm -f $(OBJ)

.PHONY: all clean
