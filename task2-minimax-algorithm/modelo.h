// modelo.h
#ifndef MODELO_H
#define MODELO_H

#include <vector>
#include <string>
#include <map>

using namespace std;

// ... (Coord e enum Piece permanecem iguais) ...

// ... (Struct Move permanece igual) ...
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

class BoardModel {
private:
    Piece tabuleiro[8][6]; 
    int cachorrosPegos;
    map<int, vector<Coord>> adj; 

    // Métodos privados auxiliares...
    int id(int r, int c) const;
    void initAdj();
    bool isPosicaoValida(int l, int c) const;
    void buscaSaltos(Coord curr, Piece tabuleiroAux[8][6], vector<Coord>& caminho, vector<Move>& movimentacoes) const;

public:
    BoardModel();
    
    void parseFromString(const char* str);
    string toHashString() const; // Para evitar repetição
    
    Piece getElemento(int r, int c) const;
    int getCachorrosPegos() const;
    Coord getOncaPos() const;
    
    void getOncaMovimentos(vector<Move>& movimentacoes) const;
    void getCachorroMovimentos(vector<Move>& moves) const;
    
    // --- MUDANÇAS AQUI ---
    void mover(const Move& m);
    void desfazer(const Move& m); // NOVO MÉTODO
    bool isFim(int& vencedor) const;
};

#endif