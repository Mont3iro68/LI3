CC = gcc

OBJ_FILES := $(patsubst ./%.c, obj/%.o, $(wildcard ./*.c))

CFLAGS = -Wall -std=c11 -g
PFLAGS = `pkg-config --cflags libxml-2.0` `pkg-config --cflags glib-2.0`
LIBS = `pkg-config --libs libxml-2.0` `pkg-config --libs glib-2.0`


program: setup $(OBJ_FILES)
	$(CC) $(CFLAGS) $(PFLAGS) $(LIBS) -o program  $(OBJ_FILES)

setup:
	mkdir -p obj

debug: CFLAGS := -g -O0
debug: program


obj/%.o: ./%.c
	$(CC) $(CFLAGS) $(PFLAGS) -o $@ -c $<

obj/program.o: interface.h parser.h avl.h utility.h Catalogo_Revisoes.h Catalogo_Artigos.h Catalogo_Contribuidores.h
obj/interface.o: interface.h 
obj/parser.o: Catalogo_Artigos.h Catalogo_Revisoes.h Catalogo_Contribuidores.h avl.h utility.h
obj/avl.o: avl.h
obj/Catalogo_Artigos.o: Catalogo_Artigos.h
obj/Catalogo_Revisoes.o: Catalogo_Revisoes.h
obj/Catalogo_Contribuidores.o: Catalogo_Contribuidores.h
obj/utility.o: utility.h

run: setup $(OBJ_FILES)
		$(CC) $(CFLAGS) $(PFLAGS) -o program $(OBJ_FILES)
		./program

clean:
		-@rm -rf obj
		-@rm program
