CC := g++ -std=c++11
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
Object_files = main.o rsdl.o Fieldrunners.o The_Runner.o Stubborn_Runner.o Super_Trooper.o Scrambler.o Gatling.o Tesla.o Missile.o Glue.o
Enemie_headers = The_Runner.hpp Stubborn_Runner.hpp Super_Trooper.hpp Scrambler.hpp 
Tower_headers = Gatling.hpp Tesla.hpp Missile.hpp Glue.hpp
 
all: FieldRunners.out

FieldRunners.out: $(Object_files)
	$(CC) $(Object_files) $(CCFLAGS) -o FieldRunners.out

rsdl.o: rsdl.hpp rsdl.cpp
	$(CC) -c rsdl.cpp 

main.o: rsdl.hpp main.cpp Fieldrunners.hpp
	$(CC) -c main.cpp 

Fieldrunners.o: Fieldrunners.cpp Fieldrunners.hpp rsdl.hpp $(Enemie_headers) $(Tower_headers)
	$(CC) -c Fieldrunners.cpp

The_Runner.o: The_Runner.cpp The_Runner.hpp rsdl.hpp
	$(CC) -c The_Runner.cpp

Stubborn_Runner.o: Stubborn_Runner.cpp Stubborn_Runner.hpp rsdl.hpp
	$(CC) -c Stubborn_Runner.cpp

Super_Trooper.o: Super_Trooper.cpp Super_Trooper.hpp rsdl.hpp
	$(CC) -c Super_Trooper.cpp

Scrambler.o: Scrambler.cpp Scrambler.hpp rsdl.hpp
	$(CC) -c Scrambler.cpp

Gatling.o: Gatling.cpp Gatling.hpp rsdl.hpp
	$(CC) -c Gatling.cpp

Tesla.o: Tesla.cpp Tesla.hpp rsdl.hpp
	$(CC) -c Tesla.cpp

Missile.o: Missile.cpp Missile.hpp rsdl.hpp
	$(CC) -c Missile.cpp

Glue.o: Glue.cpp Glue.hpp rsdl.hpp
	$(CC) -c Glue.cpp

.PHONY: clean
clean:
	rm -r *.o
	rm FieldRunners.out