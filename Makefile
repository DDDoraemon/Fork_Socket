VPATH = $(C_DIR) $(H_DIR)

TARGET := EXE/main

C_DIR := C
H_DIR := H

C_FILE_WITH_PATH := $(foreach dir, $(C_DIR), $(wildcard $(dir)/*.c))
C_FILE := $(notdir $(C_FILE_WITH_PATH))

OBJ_WITH_PATH := $(patsubst %.c, OBJ/%.o, $(C_FILE))
OBJ := $(notdir $(OBJ_WITH_PATH))

VPATH = $(C_DIR)

EXE := $(patsubst *, EXE/*, $(TARGET))

$(TARGET) : $(OBJ_WITH_PATH)
	gcc -Wall -g  $^ -o $@

$(OBJ_WITH_PATH) : OBJ/%.o : %.c
	gcc -Wall -g -c $^ -I ./$(H_DIR) -o $@



.PTHOND:clean
clean:
	rm EXE/* OBJ/*

print:
	@echo C_DIR = $(C_DIR)
	@echo C_FILE_WITH_PATH = $(C_FILE_WITH_PATH)
	@echo OBJ = $(OBJ)
	@echo EXE = $(EXE)
