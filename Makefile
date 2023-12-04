all: main.o ordenador.o csv2dat.o
	g++ main.o ordenador.o -o main
	g++ csv2dat.o -o csv2dat

main: main.o ordenador.o
	g++ main.o ordenador.o -o main

csv2dat: csv2dat.o
	g++ csv2dat.o -o csv2dat

csv2dat.o: csv2dat.cpp call911.h
	g++ -c csv2dat.cpp
	
main.o: main.cpp call911.h
	g++ -c main.cpp

ordenador.o: ordenador.cpp ordenador.h call911.h
	g++ -c ordenador.cpp

clean:
	rm *.o main csv2dat