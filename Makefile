run_main : main.o fet.o inverter.o
	g++ -g -std=c++0x -o run_main main.o fet.o inverter.o

main.o : main.cc fet.h inverter.h
	g++ -g -c -std=c++0x main.cc

fet.o : fet.cc fet.h
	g++ -g -c -std=c++0x fet.cc

inverter.o : inverter.cc inverter.h
	g++ -g -c -std=c++0x inverter.cc
