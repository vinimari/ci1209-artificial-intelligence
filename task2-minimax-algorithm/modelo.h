#ifndef MODELO_H
#define MODELO_H

#include <vector>
#include <string>
#include <map>

using namespace std;

// Estruturas básicas
struct Coord {
    int r, c;
    bool operator==(const Coord& other) const;
};

enum Piece { VAZIO = 0, ONCA = 1, CACHORRO = 2 };

struct Move {
    Coord de;
    Coord para;
    bool isSalto;
    vector<Coord> caminhoSaltosMultiplos;

    string toString(char mySide) const;
};

// Classe que representa o estado do jogo
class BoardModel {
private:
    Piece tabuleiro[8][6]; // Indices 1..7, 1..5
    int cachorrosPegos;
    map<int, vector<Coord>> adj; 

    int id(int r, int c) const;
    void initAdj();
    bool isPosicaoValida(int l, int c) const;
    void buscaSaltos(Coord curr, Piece tabuleiroAux[8][6], vector<Coord>& caminho, vector<Move>& movimentacoes) const;

public:
    BoardModel();
    
    // Parseia a string do servidor (com #) para a matriz interna
    void parseFromString(const char* str);
    
    Piece getElemento(int r, int c) const;
    int getCachorrosPegos() const;
    Coord getOncaPos() const;
    
    // Gera movimentos
    void getOncaMovimentos(vector<Move>& movimentacoes) const;
    void getCachorroMovimentos(vector<Move>& moves) const;
    
    // Aplica movimento
    void mover(const Move& m);
    
    // Verifica fim de jogo
    bool isFim(int& vencedor) const;
};

#endif
