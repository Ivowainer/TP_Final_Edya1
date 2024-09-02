CC = gcc
CFLAGS = -I./structures -I./dstar_lite
LDFLAGS = -lm -g
SRC_DIR = .
STRUCTURES_DIR = ./structures
DSTAR_DIR = ./dstar_lite

TEMP_DIR = ./temp

SRC = $(SRC_DIR)/main.c \
	  $(STRUCTURES_DIR)/bheap/bheap.c \
	  $(STRUCTURES_DIR)/node/node.c \
	  $(STRUCTURES_DIR)/list/clist.c \
	  $(DSTAR_DIR)/dstar_lite.c \

OBJ = $(SRC:.c=.o)

TARGET = robot

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
