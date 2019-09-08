# Makefile for the ZDK
# 	#$(info $$var is [${SRC}])
# $Revision:Sat Feb 23 00:47:31 EAST 2019$


MAIN := main
LIB := libzdk.a 
TARGETS := $(MAIN) $(LIB)

SRC =src
INCLUDE =-I./include
OBJ =./obj
LIBS =-L. -lzdk -lncurses -lm

FLAGS = -Wall -Werror -std=gnu99 -g

SOURCES = $(wildcard $(SRC)/*.c)
OBJECTS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

CC=gcc

all: $(MAIN)

lib: $(LIB)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -c $< $(INCLUDE) -o $@ 
	
$(LIB): $(OBJECTS) #$(LIB_SRC) $(LIB_HDR)
	ar r $@ $(OBJECTS)

main: libzdk.a
	gcc main.c -o main $(LIBS) $(INCLUDE) 

clean:
	for f in $(TARGETS) $(OBJECTS); do \
		if [ -f $${f} ]; then rm $${f}; fi; \
	done


rebuild: clean lib all
