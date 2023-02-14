CC=gcc
CFLAGS= -Wall -g -std=c99
LDFLAGS= -lm -I include -L lib -lmingw32 -lSDL2main -lSDL2 -std=c99
LDFLAGS_Linux2= -lm -I include -L lib -std=c99
LDFLAGS_Linux=`./bin/sdl2-config --cflags --libs`
SRC=main.c hello.c begin.c middle.c audio.c
OBJ =$(addprefix build/,$(SRC:.c=.o))
OBJ2=$(addprefix \build\,$(SRC:.c=.o))

exe: $(OBJ)
	$(CC) $(OBJ) -o ./bin/exe $(LDFLAGS)
exelinux: $(OBJ)
	$(CC) $(OBJ) -o ./bin/exe $(LDFLAGS_Linux)
build/%.o: src/%.c build
	$(CC) $(CFLAGS) -c $< -o $@
build/%.o: test/%.c build
	$(CC) $(CFLAGS) -c $< -o $@
build/%.o: unity/src/unity.c build
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: sdl/src/SDL.c build
	$(CC) $(CFLAGS) -c $< -o $@




build:
	mkdir build
test_exe: build/test_dummy.o build/test.o build/unity.o build/begin.o
	$(CC) $^ -o ./bin/test_exe $(LDFLAGS)
	./bin/test_exe
.PHONY: clear 
clear: 
	del bin\exe.exe
	del build\main.o
	del build\begin.o
	del build\middle.o
	del build\test.o
clearlinux: 
	rm bin\exe.exe
	rm build\main.o
	rm build\begin.o
	rm build\middle.o
	
SDL: build/test2.o build/test2.o


