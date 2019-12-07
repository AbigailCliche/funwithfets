run_main : main.o nfet.o
	g++ -g -std=c++0x -o run_main main.o nfet.o

main.o : main.cc nfet.h
	g++ -g -c -std=c++0x main.cc

nfet.o : nfet.cc nfet.h
	g++ -g -c -std=c++0x nfet.cc