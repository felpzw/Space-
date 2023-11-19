all: compile link

compile:
	g++ -c main.cpp -Isrc/include

link:
	g++ main.o -o main -Lsrc/lib -Wl,-rpath,src/lib -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f main.o main
