CC := g++ -std=c++11

CCFLAGS += -l SDL2  -l SDL2_image -l SDL2_ttf  -l SDL2_mixer

all: doodleJump.out

doodleJump.out : main.o rsdl.o enemy.o character.o spring.o platform.o mplatform.o bplatform.o
	$(CC) main.o rsdl.o enemy.o character.o spring.o platform.o mplatform.o bplatform.o $(CCFLAGS) -o doodleJump.out
	
main.o : rsdl.hpp  enemy.h character.h spring.h platform.h mplatform.h bplatform.h main.cpp
	$(CC) -c main.cpp -o main.o
	
enemy.o : rsdl.hpp enemy.h enemy.cpp
	$(CC) -c enemy.cpp -o enemy.o
	
character.o : rsdl.hpp character.h character.cpp
	$(CC) -c character.cpp -o character.o
	
spring.o : rsdl.hpp spring.h spring.cpp
	$(CC) -c spring.cpp -o spring.o
	
platform.o : rsdl.hpp platform.h platform.cpp
	$(CC) -c platform.cpp -o platform.o
	
mplatform.o : rsdl.hpp mplatform.h mplatform.cpp
	$(CC) -c mplatform.cpp -o mplatform.o
	
bplatform.o : rsdl.hpp bplatform.h bplatform.cpp
	$(CC) -c bplatform.cpp -o bplatform.o

rsdl.o : rsdl.hpp rsdl.cpp
	$(CC) -c rsdl.cpp -o rsdl.o

clean :
	rm *.o *.out
	
	
	
