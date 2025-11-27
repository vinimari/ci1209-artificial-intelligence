CFLAGS = -g -Wall -Wno-unused-result -O3
CXXFLAGS = -g -Wall -O3 -std=c++11
LDLIBS = -l hiredis -l readline

all: controlador exemplo1 exemplo2 jogador_ia

tabuleiro.o: tabuleiro.c tabuleiro.h
	gcc -c tabuleiro.c $(CFLAGS)

controlador: controlador.c
	gcc $(CFLAGS) -o controlador controlador.c $(LDLIBS)

exemplo1: tabuleiro.o exemplo1.c
	gcc $(CFLAGS) -o exemplo1 tabuleiro.o exemplo1.c $(LDLIBS)

exemplo2: tabuleiro.o exemplo2.c
	gcc $(CFLAGS) -o exemplo2 tabuleiro.o exemplo2.c $(LDLIBS)

modelo.o: modelo.cpp modelo.h
	g++ -c modelo.cpp $(CXXFLAGS)

heuristica.o: heuristica.cpp heuristica.h modelo.h
	g++ -c heuristica.cpp $(CXXFLAGS)

ia.o: ia.cpp ia.h modelo.h heuristica.h
	g++ -c ia.cpp $(CXXFLAGS)

main.o: main.cpp modelo.h ia.h tabuleiro.h
	g++ -c main.cpp $(CXXFLAGS)

jogador_ia: tabuleiro.o modelo.o heuristica.o ia.o main.o
	g++ -o jogador_ia tabuleiro.o modelo.o heuristica.o ia.o main.o $(LDLIBS)

clean:
	rm -f controlador exemplo1 exemplo2 jogador_ia *.o
